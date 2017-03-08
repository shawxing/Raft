/*
 * Util.h
 *
 *  Created on: 2017年3月1日
 *      Author: xiaoxing
 */

#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_
#include <deque>
#include <cmath>
#include "../kvproto/src/eraftpb.pb.h"

using namespace eraftpb;

namespace Util {

template<class T>
void limit_size(std::deque<T>* entries, uint64_t max) {
	if (entries->empty()) {
		return;
	}

	size_t size = (*entries)[0].ByteSizeLong();
	uint32_t limit = 1;
	while (limit < entries->size()) {
		size += (*entries)[limit].ByteSizeLong();
		if (size > max) {
			break;
		}

		++limit;
	}

	entries->erase(entries->begin() + limit, entries->end());
}

uint64_t
randomRange(uint64_t start, uint64_t end)
{
    return uint64_t(lround(randomRangeDouble(double(start), double(end))));
}

} /* namespace Util */

#endif /* UTIL_UTIL_H_ */
