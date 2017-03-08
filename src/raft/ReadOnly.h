/*
 * ReadOnly.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef READONLY_H_
#define READONLY_H_

#include <vector>
using namespace std;

namespace Raft {

enum ReadOnlyOption{
    Safe,
    LeaseBased,
};

struct ReadState{
    uint64_t index;
    vector<char> request_ctx;
};

class ReadOnly {
public:
	ReadOnly();
	~ReadOnly();
};

} /* namespace Raft */

#endif /* READONLY_H_ */
