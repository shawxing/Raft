/*
 * Progress.cpp
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#include "../raft/Progress.h"

namespace Raft {

Inflights::Inflights(size_t cap) :
		start(0), count(0) {
	buffer.reserve(cap);
}

bool Inflights::full() {
	return count == cap();
}

size_t Inflights::cap() {
	return buffer.capacity();
}

void Inflights::add(uint64_t inflight) {
	if (full) {
		PANIC("cannot add into a full inflights");
	}

	size_t next = start + count;
	if (next > cap()) {
		next -= cap();
	}

	assert(next <= buffer.size());

	if (next == buffer.size()) {
		buffer.push_back(inflight);
	} else {
		buffer[next] = inflight;
	}

	++count;
}

void Inflights::free_to(uint64_t to) {
	if (count == 0 || to < buffer[start]) {
		return;
	}

	size_t i = 0;
	size_t idx = start;
	while (i < idx) {
		if (to < buffer[idx]) {
			break;
		}

		++idx;
		if (idx >= cap()) {
			idx -= cap();
		}

		++i;
	}

	count -= i;
	start = idx;
}

void Inflights::free_first_one() {
	uint64_t startV = buffer[start];
	free_to(startV);
}

Inflights::~Inflights() {
}

void Inflights::reset() {
	count = 0;
	start = 0;
}

Progress::Progress(uint64_t next_idx, size_t ins_size) :
		matched(0), paused(false), state(ProgressState::Probe), next_idx(next_idx), recent_active(
				false), ins(new Inflights(ins_size)), pending_snapshot(0) {

}

Progress::~Progress() {
	if (ins) {
		delete ins;
	}
}

void Progress::reset_state(ProgressState ps) {
	paused = false;
	pending_snapshot = 0;
	state = ps;
	ins->reset();
}

void Progress::become_probe() {
	if (state == ProgressState::Snapshot) {
		bool ispending = pending_snapshot;
		reset_state(ProgressState::Probe);
		next_idx = std::max<uint64_t>(matched + 1, pending_snapshot + 1);
	} else {
		reset_state(ProgressState::Probe);
		next_idx = matched + 1;
	}
}

void Progress::become_replicate() {
	reset_state(ProgressState::Replicate);
	next_idx = matched + 1;
}

void Progress::become_snapshot(uint64_t snapshot_idx) {
	reset_state(ProgressState::Snapshot);
	pending_snapshot = snapshot_idx;
}

void Progress::snapshot_failure() {
	pending_snapshot = 0;
}

bool Progress::maybe_snapshot_abort() {
	return state == ProgressState::Snapshot && matched >= pending_snapshot;
}

bool Progress::maybe_update(uint64_t n) {
	bool need_update = matched < n;
	if (need_update) {
		matched = n;
		resume();
	}

	if (next_idx < n + 1) {
		next_idx = n + 1;
	}

	return need_update;

}

void Progress::optimistic_update(uint64_t n) {
	next_idx = n + 1;
}

bool Progress::maybe_decr_to(uint64_t rejected, uint64_t last) {
	if (state == ProgressState::Replicate) {
		if (rejected < matched) {
			return false;
		}
		next_idx = matched + 1;
		return true;
	}

	if (next_idx == 0 || next_idx - 1 != rejected) {
		return false;
	}

	next_idx = std::min<uint64_t>(rejected, last + 1);
	if (next_idx < 1) {
		next_idx = 1;
	}
	resume();
	return true;
}

bool Progress::is_paused() {
	bool p = false;
	switch (state) {
	case ProgressState::Probe:
		p = paused;
		break;
	case ProgressState::Replicate:
		p = ins->full();
		break;
	case ProgressState::Snapshot:
		p = true;
	}

	return p;
}

void Progress::resume() {
	paused = false;
}

void Progress::pause() {
	paused = true;
}

} /* namespace Raft */

