/*
 * Unstable.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef UNSTABLE_H_
#define UNSTABLE_H_

#include "../kvproto/src/eraftpb.pb.h"
#include "../util/log.h"
#include <deque>
#include <string>

using namespace eraftpb;
using namespace std;
using namespace Util;

namespace Raft {

class Unstable {
public:
	Unstable(uint64_t offset, string tag);
	~Unstable();

public:
	Snapshot* snapshot;
	deque<Entry> entries;
	uint64_t offset;
	string tag;

public:
	bool maybe_first_index(uint64_t& index);
	bool maybe_last_index(uint64_t& index);
	bool maybe_term(uint64_t idx,uint64_t& term);
	void stable_to(uint64_t idx,uint64_t term);
	void stable_snap_to(uint64_t idx);
	void restore(Snapshot* snap);
	void truncate_and_appand(deque<Entry>* ents);
	void must_check_outofbounds(const uint64_t lo,const uint64_t hi);
	void slice(uint64_t lo,uint64_t hi,deque<Entry>* ents);
};

} /* namespace Raft */

#endif /* UNSTABLE_H_ */
