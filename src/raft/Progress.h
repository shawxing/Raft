/*
 * Progress.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef PROGRESS_H_
#define PROGRESS_H_

#include "../util/Log.h"
#include <vector>
#include <assert.h>

using namespace Util;
using namespace std;

namespace Raft {

enum ProgressState {
	Probe, Replicate, Snapshot,
};

class Inflights {
public:
	Inflights(size_t cap);
	~Inflights();

public:
	size_t start;
	size_t count;
	vector<uint64_t> buffer;

public:
	bool full();
	size_t cap();
	void add(uint64_t inflight);
	void free_to(uint64_t to);
	void free_first_one();
	void reset();
};

class Progress {
public:
	Progress(uint64_t next_idx, size_t ins_size);
	~Progress();

public:
	uint64_t matched;
	uint64_t next_idx;
	ProgressState state;
	bool paused;
	uint64_t pending_snapshot;
	bool recent_active;
	Inflights* ins;

public:
	void reset_state(ProgressState ps);
	void become_probe();
	void become_replicate();
	void become_snapshot(uint64_t snapshot_idx);
	void snapshot_failure();
	bool maybe_snapshot_abort();
	bool maybe_update(uint64_t n);
	void optimistic_update(uint64_t n);
	bool maybe_decr_to(uint64_t rejected,uint64_t last);
	bool is_paused();
	void resume();
	void pause();
};

} /* namespace Raft */

#endif /* PROGRESS_H_ */
