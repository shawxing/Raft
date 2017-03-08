/*
 * RawNode.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef RAWNODE_H_
#define RAWNODE_H_

#include "../kvproto/src/eraftpb.pb.h"
using namespace eraftpb;


namespace Raft {

class RawNode {
public:
	RawNode();
	~RawNode();
};

bool IsEmptyHardState(HardState& hs){
	if(hs.term() == 0 && hs.commit() ==0 && hs.vote()==0)
		return true;

	return false;
}
} /* namespace Raft */

#endif /* RAWNODE_H_ */
