/*
 * Unstable.cpp
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#include "../raft/Unstable.h"

namespace Raft {

Unstable::Unstable(uint64_t offset, string tag) :
		snapshot(NULL), offset(offset), tag(tag) {

}

Unstable::~Unstable() {
}

bool Unstable::maybe_first_index(uint64_t& index) {
	if (snapshot != NULL) {
		index = snapshot->metadata().index() + 1;
		return true;
	}

	return false;
}

bool Unstable::maybe_last_index(uint64_t& index) {
	size_t l = entries.size();
	if (l != 0) {
		index = offset + uint64_t(l) - 1;
		return true;
	}
	if (snapshot != NULL) {
		index = snapshot->metadata().index();
		return true;
	}

	return false;
}

bool Unstable::maybe_term(uint64_t idx, uint64_t& term) {
	if (idx < offset) {
		if (snapshot == NULL) {
			return false;
		}
		if (snapshot->metadata().index() == idx) {
			term = snapshot->metadata().term();
			return true;
		}

		return false;
	}

	uint64_t ilast;
	if (!maybe_last_index(ilast)) {
		return false;
	}
	if (idx > ilast) {
		return false;
	}

	term = entries[idx - offset].term();
	return true;
}

void Unstable::stable_to(uint64_t idx, uint64_t term) {
	uint64_t t;
	if (!maybe_term(idx, t)) {
		return;
	}

	if (t == term && idx > offset) {
//		entries = vector<uint64_t>(entries.begin() + idx + 1 - offset,
//				entries.end());
		entries.erase(entries.begin(), entries.begin() + idx + 1 - offset);
		offset = idx + 1;
	}
}

void Unstable::stable_snap_to(uint64_t idx) {
	if (snapshot == NULL) {
		return;
	}
	if (idx == snapshot->metadata().index()) {
		snapshot = NULL;
	}
}

void Unstable::restore(Snapshot* snap) {
	entries.clear();
	offset = snap->metadata().index() + 1;
	snapshot = snap;
}

void Unstable::truncate_and_appand(deque<Entry>* ents) {
	uint64_t after = (*ents)[0].index();
	if (after == offset + entries.size()) {
		entries.insert(entries.end(), ents->begin(), ents->end());
	} else if (after <= offset) {
		offset = after;
		entries.clear();
		entries.insert(entries.begin(), ents->begin(), ents->end());
	} else {
		must_check_outofbounds(offset, after);
		entries.erase(entries.begin() + (after - offset), entries.end());
		entries.insert(entries.end(), ents->begin(), ents->end());
	}
}

void Unstable::must_check_outofbounds(const uint64_t lo, const uint64_t hi) {
	if (lo > hi) {
		PANIC("%s invalid unstable.slice %" PRIu64 " > %" PRIu64, tag.c_str(), lo,
				hi);
	}
	uint64_t upper = offset + entries.size();
	if (lo < offset || hi > upper) {
		PANIC(
				"%s unstable.slice[%" PRIu64 ", %" PRIu64 "] out of bound[%" PRIu64 ", %" PRIu64 "]",
				tag.c_str(), lo, hi, offset, upper);
	}
}

void Unstable::slice(uint64_t lo, uint64_t hi, deque<Entry>* ents) {
	must_check_outofbounds(lo, hi);
	ents->insert(ents->end(),entries.begin() + lo - offset, entries.begin() + hi - offset);
}

} /* namespace Raft */

