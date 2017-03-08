/*
 * RaftLog.cpp
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#include "RaftLog.h"

namespace Raft {

#define NO_LIMIT std::numeric_limits<uint64_t>::max()

RaftLog::RaftLog(Storage* store, string tag) :
		store(store), tag(tag), unstable(NULL), committed(0), applied(0) {
}

RaftLog::~RaftLog() {
	if (unstable) {
		delete unstable;
	}
}

void RaftLog::init() {
	if (store == NULL) {
		PANIC("storage must not be nil");
	}
	ErrorInfo error;
	uint64_t first_index;
	if (!store->first_index(first_index)(error)) {
		PANIC("%s", error._info.c_str());
	}
	uint64_t last_index;
	if (!store->last_index(last_index)(error)) {
		PANIC("%s", error._info.c_str());
	}

	// Initialize committed and applied pointers to the time of the last compaction.
	unstable = new Unstable(last_index + 1, tag);
	committed = first_index - 1;
	applied = first_index - 1;
}

Storage* RaftLog::get_store() {
	return store;
}

Unstable* RaftLog::get_unstable() {
	return unstable;
}

bool RaftLog::term(uint64_t idx, uint64_t& term) {
	uint64_t dummy_idx = first_index() - 1;
	if (idx < dummy_idx || idx > last_index()) {
		term = 0;
		return true;
	}

	if (unstable->maybe_term(idx, term)) {
		return true;
	}

	ErrorInfo errinfo;
	if (!store->term(idx, term)(errinfo)) {
		if (errinfo.ErrType() == ErrType::Compacted
				|| errinfo.ErrType() == ErrType::Unavailable) {
			term = 0;
			return false;
		} else {
			PANIC("%s", errinfo.Info().c_str());
		}
	}

	return true;
}

uint64_t RaftLog::first_index() {
	uint64_t idx;
	if (unstable->maybe_first_index(idx)) {
		return idx;
	}
	ErrorInfo errinfo;
	if (!store->first_index(idx)(errinfo)) {
		PANIC("%s", errinfo.Info().c_str());
	}

	return idx;
}

uint64_t RaftLog::last_index() {
	uint64_t idx;
	if (unstable->maybe_last_index(idx)) {
		return idx;
	}
	ErrorInfo errinfo;
	if (!store->last_index(idx)(errinfo)) {
		PANIC("%s", errinfo.Info().c_str());
	}

	return idx;
}

bool RaftLog::match_term(uint64_t idx, uint64_t term) {
	uint64_t t;
	if (!term(idx, t)) {
		return false;
	}

	return t == term;
}

uint64_t RaftLog::find_conflict(deque<Entry>* ents) {
	for (auto &e : ents) {
		if (!match_term(e.get_index(), e.get_term())) {
			if (e.get_index() <= last_index()) {
				uint64_t t;
				NOTICE(
						"%s found conflict at index %" PRIu64 ", [existing term: %" PRIu64 "}, conflicting term:%" PRIu64 "]",
						tag.c_str(), e.get_index(), term(e.get_index(), t) ? t : 0,
						e.get_term());
			}
			return e.get_index();
		}
	}

	return 0;
}

uint64_t RaftLog::append(deque<Entry>* ents) {
	if (ents->empty()) {
		return last_index();
	}

	uint64_t after = (*ents)[0].index() - 1;
	if (after < committed) {
		PANIC("%s after %" PRIu64 " is out of range [committed " PRIu64 "]",
				tag.c_str(), after, committed);
	}

	unstable->truncate_and_appand(ents);
	return last_index();
}

bool RaftLog::maybe_append(uint64_t idx, uint64_t term, uint64_t commit,
		deque<Entry>* ents, uint64_t& lastidx) {
	uint64_t last_new_index = idx + ents->size();
	bool ret = false;
	if (match_term(idx, term)) {
		uint64_t conflict_idx = find_conflict(ents);
		if (conflict_idx == 0) {
		} else if (conflict_idx <= committed) {
			PANIC("%s entry %" PRIu64 " conflict with committed entry %" PRIu64,
					tag.c_str(), conflict_idx, committed);
		} else {
			uint64_t offset = idx + 1;
			ents->erase(ents->begin(), ents->begin() + (conflict_idx - offset));
			append(ents);
		}
		commit_to(std::min(committed, last_new_index));
		lastidx = last_new_index;
		return true;
	}

	return false;
}

void RaftLog::commit_to(uint64_t to_commit) {
	if (committed >= to_commit) {
		return;
	}
	if (last_index() < to_commit) {
		PANIC("%s to_commit %" PRIu64 " is out of range [last_index %" PRIu64 "]",
				tag.c_str(), to_commit, last_index());
	}
	committed = to_commit;
}

void RaftLog::applied_to(uint64_t idx) {
	if (idx == 0) {
		return;
	}
	if (committed < idx || idx > applied) {
		PANIC(
				"%s applied(%" PRIu64 ") is out of range [prev_applied(%" PRIu64 "), committed(%" PRIu64 ")",
				tag.c_str(), idx, applied, committed);
	}
	applied = idx;
}

uint64_t RaftLog::get_applied() {
	return applied;
}

void RaftLog::stable_to(uint64_t idx, uint64_t term) {
	unstable->stable_to(idx, term);
}

void RaftLog::stable_snap_to(uint64_t idx) {
	unstable->stable_snap_to(idx);
}

vector<Entry>* RaftLog::unstable_entries() {
	if (unstable->entries.empty()) {
		return NULL;
	}

	return &(unstable->entries);
}

Result<ErrorInfo> RaftLog::must_check_outofbounds(uint64_t low, uint64_t high) {
	if (low > high) {
		PANIC("%s invalid slice %" PRIu64 " > %" PRIu64, tag.c_str(), low, high);
	}
	uint64_t first_index = first_index();
	if (low < first_index) {
		return {ErrorInfo("",ErrType::Compacted)};
	}
	uint64_t length = last_index() + 1 - first_index;
	if (low < first_index || high > first_index + length) {
		PANIC(
				"%s slice[%" PRIu64 ", %" PRIu64 "] out of bound[%" PRIu64 ",%" PRIu64 "]",
				tag.c_str(), low, high, first_index, last_index());
	}

	return {};

}

// slice returns a slice of log entries from lo through hi-1, inclusive.
Result<ErrorInfo> RaftLog::slice(uint64_t low, uint64_t high, uint64_t max_size,
		deque<Entry>* ents) {
	ErrorInfo err;
	Result<ErrorInfo> result = must_check_outofbounds(low, high);
	if (!result(err)) {
		return result;
	}

	if (low == high) {
		ents->resize(0);
		return {};
	}

	if (low < unstable->offset) {
		result = store->entries(low, std::min(high, unstable->offset), max_size,
				ents);
		if (!result(err)) {
			if (err.ErrType() == ErrType::Compacted) {
				return result;
			} else if (err.ErrType() == ErrType::Unavailable) {
				PANIC("%s entries[%" PRIu64 ":%" PRIu64 "] is unavailable from storage",
						tag.c_str(), low, std::min(high, unstable->offset));
			} else {
				PANIC("%s unexpected error: %s", tag.c_str(), err.Info().c_str());
			}
		}

		if (ents->size() < std::min(high, unstable->offset) - low) {
			return {};
		}
	}
	if (high > unstable->offset) {
		unstable->slice(std::max(low, unstable->offset), high, ents);
	}

	limit_size(ents, max_size);
	return {};
}

Result<ErrorInfo> RaftLog::entries(uint64_t idx, uint64_t max_size,
		deque<Entry>* ents) {
	uint64_t last = last_index();
	if (idx > last) {
		return {};
	}

	return slice(idx, last + 1, max_size, ents);
}

bool RaftLog::maybe_commit(uint64_t max_index, uint64_t term) {
	uint64_t t;
	if (!term(max_index, t)) {
		t = 0;
	}
	if (max_index > committed && t == term) {
		commit_to(max_index);
		return true;
	}
	return false;
}

void RaftLog::all_entries(deque<Entry>* ents) {
	uint64_t first_index = first_index();
	ErrorInfo err;
	if (!entries(first_index, NO_LIMIT, ents)(err)) {
		// try again if there was a racing compaction
		if (err.ErrType() == ErrType::Compacted) {
			all_entries(ents);
			return;
		}
		PANIC("%s unexpected error: %s", tag.c_str(), err.Info().c_str());
	}
}

void RaftLog::restore(Snapshot* snapshot) {
	NOTICE("{} log [{}] starts to restore snapshot [index: {}, term: {}]",
			tag.c_str(), to_string().c_str(), snapshot->metadata().index(),
			snapshot->metadata().term());
	committed = snapshot->metadata().index();
	unstable->restore(snapshot);
}

string RaftLog::to_string() {
	return StringUtil::format(
			"committed=%" PRIu64 ", applied=%" PRIu64 ", unstable.offset=%" PRIu64 ", unstable.entries.len()=%" PRIu64,
			committed, applied, unstable->offset, unstable->entries.size());
}

uint64_t RaftLog::last_term() {
	uint64_t t;
	if (!term(last_index(), t)) {
		PANIC("%s unexpected error when getting the last term", tag.c_str());
	}

	return t;
}

bool RaftLog::is_up_to_date(uint64_t last_index, uint64_t term) {
	return term > last_term()
			|| (term == last_term() && last_index > last_index());
}

} /* namespace Raft */

