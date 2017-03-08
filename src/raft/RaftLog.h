/*
 * RaftLog.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef RAFTLOG_H_
#define RAFTLOG_H_
#include <string>

#include "Storage.h"
#include "Unstable.h"
#include "../util/Log.h"
#include "../util/Result.h"
#include "../kvproto/src/eraftpb.pb.h"
#include "../util/util.h"
#include "../util/StringUtil.h"

using namespace Util;
using namespace eraftpb;

namespace Raft {

#define NO_LIMIT std::numeric_limits<uint64_t>::max()

class RaftLog {
public:
	RaftLog(Storage* store, string tag);
	~RaftLog();

	void init();
public:
	Storage* store;
	Unstable* unstable;
	uint64_t committed;
	uint64_t applied;
	string tag;

public:
	inline Storage* get_store();
	inline Unstable* get_unstable();
	bool term(uint64_t idx, uint64_t& term);
	uint64_t first_index();
	uint64_t last_index();
	uint64_t last_term();
	bool match_term(uint64_t idx, uint64_t term);
	uint64_t find_conflict(deque<Entry>* ents);
	uint64_t append(deque<Entry>* ents);
	bool maybe_append(uint64_t idx, uint64_t term, uint64_t commit, deque<Entry>* ents, uint64_t& lastidx);
	void commit_to(uint64_t to_commit);
	bool maybe_commit(uint64_t max_index,uint64_t term);
	void applied_to(uint64_t idx);
	uint64_t get_applied();
	void stable_to(uint64_t idx,uint64_t term);
	void stable_snap_to(uint64_t idx);
	vector<Entry>* unstable_entries();
	Result<ErrorInfo> must_check_outofbounds(uint64_t low,uint64_t high);
	Result<ErrorInfo> slice(uint64_t low,uint64_t high,uint64_t max_size,deque<Entry>* ents);
	Result<ErrorInfo> entries(uint64_t idx,uint64_t max_size,deque<Entry>* ents);
	void all_entries(deque<Entry>* ents);
	void restore(Snapshot* snap);
	string to_string();
	bool is_up_to_date(uint64_t last_index,uint64_t term);
};

} /* namespace Raft */

#endif /* RAFTLOG_H_ */
