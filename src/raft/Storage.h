/*
 * Storage.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef STORAGE_H_
#define STORAGE_H_

#include "../kvproto/src/eraftpb.pb.h"
#include "../util/Result.h"
#include <deque>

using namespace Util;
using namespace eraftpb;


namespace Raft {
struct RaftState
{
	HardState hard_state;
	ConfState conf_state;
};

class Storage {
public:
	Storage();
	virtual ~Storage();

	Result<ErrorInfo> initial_state(RaftState& state) = 0;
	Result<ErrorInfo> entries(uint64_t low,uint64_t high,uint64_t max_size,deque<Entry>* entries)= 0;
	Result<ErrorInfo> term(uint64_t idx,uint64_t& term) = 0;
	Result<ErrorInfo> first_index(uint64_t& index) = 0;
	Result<ErrorInfo> last_index(uint64_t& index) = 0;
	Result<ErrorInfo> snapshot(Snapshot& snapshot) = 0;
};

} /* namespace Raft */

#endif /* STORAGE_H_ */
