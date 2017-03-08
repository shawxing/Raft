/*
 * Raft.cpp
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#include "Raft.h"

namespace Raft {

Result<ErrorInfo> Config::validate() const {
	if (id == INVALID_ID)
		return {ErrorInfo("invalid node id",ErrType::Other)};
	if (heartbeat_tick == 0)
		return {ErrorInfo("heartbeat tick must greater than 0",ErrType::Other)};
	if (election_tick <= heartbeat_tick)
		return {ErrorInfo("election tick must be greater than heartbeat tick",ErrType::Other)};
	if (max_inflight_msgs == 0)
		return {ErrorInfo("max inflight messages must be greater than 0",ErrType::Other)};

	return {};
}

Raft::Raft(Config* c) :
		id(c->id), term(0), vote(0), max_inflight(c->max_inflight_msgs), max_msg_size(
				c->max_size_per_msg), state(StateRole::Follower), leader_id(0), lead_transferee(
				0), pending_conf(false), election_elapsed(0), heartbeat_elapsed(0), heartbeat_elapsed(
				c->heartbeat_tick), check_quorum(c->check_quorum), pre_vote(
				c->pre_vote), heartbeat_timeout(c->heartbeat_tick), election_timeout(
				c->election_tick), randomized_election_timeout(0), tag(c->tag) {
}

Raft* Raft::new_Raft(Config* c, Storage* store) {
	ErrorInfo error;
	if (!c->validate()(error)) {
		PANIC("configuration is invalid(%s)", error.Info().c_str());
	}
	RaftState rs;
	if (!store->initial_state(rs)(error)) {
		PANIC("%s", error.Info().c_str());
	}

	Raft *r = new Raft(c);
	unique_ptr<RaftLog> raftlog(new RaftLog(store, c->tag));
	r->raft_log = std::move(raftlog);
	::google::protobuf::RepeatedField<uint64_t>& peers = c->peers;
	if (!rs.conf_state.nodes().empty()) {
		if (!peers.empty()) {
			PANIC("%s cannot specify both newRaft(peers) and ConfState.Nodes)",
					r->tag.c_str());
		}
		peers = rs.conf_state.nodes();
	}

	unique_ptr<ReadOnly> readonly(new ReadOnly(c->read_only_option));
	r->read_only = std::move(readonly);

	string strnodes;
	for (auto it = peers.begin(); it != peers.end(); ++it) {
		unique_ptr<Progress> pro(new Progress(1, r->max_inflight));
		r->prs.insert(
				std::pair<uint64_t, unique_ptr<Progress>>(*it, std::move(pro)));
		strnodes += StringUtil::format("%" PRIu64, *it);
		if (it != peers.end() - 1) {
			strnodes += ",";
		}
	}

	if (!IsEmptyHardState(rs.hard_state)) {
		r->load_state(rs.hard_state);
	}

	if (c->applied > 0) {
		r->raft_log->applied_to(c->applied);
	}

	r->become_follower(r->term, INVALID_ID);

	NOTICE(
			"%s newRaft [peers: %s, term: %" PRIu64 ", commit: %" PRIu64 ", applied: %" PRIu64 ", last_index: %" PRIu64 ", \
      last_term: %" PRIu64 "]",
			r->tag.c_str(), strnodes.c_str(), r->term, r->raft_log->committed,
			r->raft_log->get_applied(), r->raft_log->last_index(),
			r->raft_log->last_term());

	return r;
}

void Raft::tick() {
	if (state == StateRole::Follower || state == StateRole::PreCandidate
			|| state == StateRole::Candidate) {
		tick_election();
	} else if (state == StateRole::Leader) {
		tick_heartbeat();
	}
}

void Raft::load_state(HardState& hs) {
	if (hs.commit() < raft_log->committed
			|| hs.commit() > raft_log->last_index()) {
		PANIC("%s hs.commit %s is out of range [%s, %s]", tag.c_str(), hs.commit(),
				raft_log->committed, raft_log->last_index());
	}
	raft_log->committed = hs.commit();
	term = hs.term();
	vote = hs.vote();
}

Raft::~Raft() {
}

void Raft::become_follower(uint64_t term, uint64_t leader_id) {
}

void Raft::become_leader() {
}

void Raft::become_candidate() {
}

void Raft::reset(uint64_t term) {
	if (this->term != term) {
		this->term = term;
		vote = INVALID_ID;
	}

	leader_id = INVALID_ID;
	reset_randomized_election_timeout();
	election_elapsed = 0;
	heartbeat_elapsed = 0;

	abort_leader_transfer();
	votes.clear();
	uint64_t last_index = raft_log->last_index();
	for (auto &i : prs) {
		unique_ptr<Progress> pro(new Progress(last_index, max_inflight));
		i.second = std::move(pro);
		if (i.first == id) {
			i.second->matched = last_index;
		}
	}
	pending_conf = false;

	unique_ptr<ReadOnly> readonly(new ReadOnly(read_only->option));
	read_only = std::move(readonly);
}

void Raft::reset_randomized_election_timeout() {
	randomized_election_timeout = Random::randomRange(election_timeout,
			election_timeout * 2);
}

void Raft::abort_leader_transfer() {
	lead_transferee = 0;
}

void Raft::tick_election() {
	election_elapsed += 1;
	if (promotable() && pass_election_timeout()) {
		election_elapsed = 0;
		eraftpb::Message message;
		message.set_to(INVALID_ID);
		message.set_msg_type(eraftpb::MessageType::MsgHup);
		message.set_from(this->id);
		step(message);
	}
}

void Raft::tick_heartbeat() {
}

bool Raft::promotable() {
	auto it = prs.find(this->id);
	if (it != prs.end()) {
		return true;
	}

	return false;
}

bool Raft::promotable() {
}

bool Raft::pass_election_timeout() {
	return election_elapsed >= randomized_election_timeout;
}

Result<ErrorInfo> Raft::step(eraftpb::Message& m) {
	if (m.term() == 0) {
	} else if (m.term() > this->term) {
		uint64_t leader_id = m.from();
		if (m.msg_type() == eraftpb::MessageType::MsgRequestVote
				|| m.msg_type() == eraftpb::MessageType::MsgRequestPreVote) {
			bool force = m.context() == CAMPAIGN_TRANSFER;
			bool in_lease = this->check_quorum && leader_id != INVALID_ID
					&& this->election_elapsed < this->election_timeout;
			if (!force && in_lease) {
				NOTICE(
						"%s [logterm: %" PRIu64 ", index: %" PRIu64 ", vote: %" PRIu64 "] ignored %d vote from \
            %" PRIu64 " [logterm: %" PRIu64 ", index: %" PRIu64 "] at term %" PRIu64 ": lease is not expired \
            (remaining ticks: %" PRIu64 ")",
						tag.c_str(), raft_log->last_term(), raft_log->last_index(),
						this->vote, m.msg_type(), m.from(), m.log_term(), m.index(),
						this->term, this->election_timeout - this->election_elapsed);
				return {};
			}

			leader_id = INVALID_ID;
		}

		if (m.msg_type() == eraftpb::MessageType::MsgRequestPreVote
				|| (m.msg_type() == eraftpb::MessageType::MsgRequestPreVoteResponse
						&& !m.reject())) {
		} else {
			NOTICE(
					"%s [term: %" PRIu64 "] received a %d message with higher term from %" PRIu64 " [term: %" PRIu64 "]",
					tag.c_str(), this->term, m.msg_type(), m.from(), m.term());

			become_follower(m.term(), leader_id);
		}
	} else if (m.term() < this->term) {
		if (this->check_quorum
				&& (m.msg_type() == eraftpb::MessageType::MsgHeartbeat
						|| m.msg_type() == eraftpb::MessageType::MsgAppend)) {
			eraftpb::Message to_send;
			to_send.set_to(m.from());
			to_send.set_msg_type(eraftpb::MessageType::MsgAppendResponse);
			this->send(to_send);
		} else {
			NOTICE(
					"%s [term: %" PRIu64 "] ignored a %d message with lower term from %" PRIu64 " [term: %" PRIu64 "]",
					tag.c_str(), this->term, m.msg_type(), m.from(), m.term());
		}

		return {};
	}

	//todo:call before_step_state?

	ErrorInfo err;
	switch (m.msg_type()) {
	case eraftpb::MessageType::MsgHup:
		if (state != StateRole::Leader) {
			deque<Entry> ents;
			if (!raft_log->slice(raft_log->applied + 1, raft_log->committed + 1,
			NO_LIMIT,&ents)(err)) {
				PANIC("unexpected error getting unapplied entries");
			}
			int n = num_pending_conf(ents);
			if (n != 0 && raft_log->committed > raft_log->applied) {
				WARNING(
						"%s cannot campaign at term %" PRIu64 " since there are still %d pending configuration changes to apply",
						tag.c_str(), term, n);

				return {};
			}

			NOTICE("%s is starting a new election at term %" PRIu64, tag.c_str(),
					term);
			if (pre_vote) {
				campaign(CAMPAIGN_PRE_ELECTION);
			} else {
				campaign(CAMPAIGN_ELECTION);
			}
		} else {

		}
		break;
	}
}

void Raft::send(eraftpb::Message& m) {

}

int Raft::num_pending_conf(deque<Entry>& ents) {
	int count = 0;
	for (auto &i : ents) {
		if (i.entry_type() == EntryType::EntryConfChange) {
			++count;
		}
	}

	return count;
}

void Raft::campaign(const string& campain_type) {
}

void Raft::become_pre_candidate() {
}

} /* namespace Raft */
