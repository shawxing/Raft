/*
 * Raft.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef RAFT_H_
#define RAFT_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <deque>

#include "ReadOnly.h"
#include "RaftLog.h"
#include "Progress.h"
#include "Storage.h"
#include "RawNode.h"
#include "../util/Result.h"
#include "../kvproto/src/msgpb.pb.h"
#include "../kvproto/src/eraftpb.pb.h"
#include "../util/Log.h"
#include "../util/random.h"

using namespace std;
using namespace Util;
using namespace msgpb;
using namespace eraftpb;

namespace Raft {

static const string CAMPAIGN_PRE_ELECTION = "CampaignPreElection";
static const string CAMPAIGN_ELECTION = "CampaignElection";
static const string CAMPAIGN_TRANSFER = "CampaignTransfer";

const int64_t INVALID_ID = 0;
const int64_t INVALID_INDEX = 0;

enum StateRole {
	Follower, Candidate, Leader, PreCandidate,
};

struct Config {
	uint64_t id;
	::google::protobuf::RepeatedField<uint64_t> peers;
	uint election_tick;
	uint heartbeat_tick;
	uint64_t applied;
	uint64_t max_size_per_msg;
	uint64_t max_inflight_msgs;bool check_quorum;bool pre_vote;
	ReadOnlyOption read_only_option;
	string tag;

	Result<ErrorInfo> validate() const;
};

struct SoftState {
	uint64_t leader_id;
	StateRole raft_state;
};

class Raft {
public:
	Raft(Config* c);
	static Raft* new_Raft(Config* c, Storage* store);
	~Raft();

public:
	uint64_t id;
	uint64_t term;
	uint64_t vote;
	vector<ReadState> read_states;
	unique_ptr<RaftLog> raft_log;
	size_t max_inflight;
	uint64_t max_msg_size;
	map<uint64_t, unique_ptr<Progress>> prs;
	StateRole state;
	map<uint64_t, bool> votes;
	vector<eraftpb::Message> msgs;
	uint64_t leader_id;
	uint64_t lead_transferee;bool pending_conf;
	unique_ptr<ReadOnly> read_only;
	size_t election_elapsed;
	size_t heartbeat_elapsed;bool check_quorum;bool pre_vote;
	size_t heartbeat_timeout;
	size_t election_timeout;
	size_t randomized_election_timeout;
	std::function<bool(eraftpb::Message&)> before_step_state;
	string tag;

public:
	inline Storage* get_store() {
		return raft_log->get_store();
	}

	void tick();
	void tick_election();
	void tick_heartbeat();
	Result<ErrorInfo> step(eraftpb::Message& m);
	void campaign(const string& campain_type);
	void send(eraftpb::Message& m);
	bool promotable();
	int num_pending_conf(deque<Entry>& ents);
	bool pass_election_timeout();
	void reset(uint64_t term);
	void reset_randomized_election_timeout();
	void abort_leader_transfer();
	void load_state(HardState& hs);
	void become_follower(uint64_t term, uint64_t leader_id);
	void become_leader();
	void become_candidate();
	void become_pre_candidate();
};

} /* namespace Raft */

#endif /* RAFT_H_ */
