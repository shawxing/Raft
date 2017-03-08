/*
 * Result.h
 *
 *  Created on: 2017年2月21日
 *      Author: xiaoxing
 */

#ifndef UTIL_RESULT_H_
#define UTIL_RESULT_H_

#include <string>
#include <functional>

using namespace std;

namespace Util {

enum ErrType {
	Compacted,
	Unavailable,
	SnapshotOutOfDate,
	SnapshotTemporarilyUnavailable,
	Other,
};

struct ErrorInfo {
	ErrorInfo() :
			_type(ErrType::Other) {
	}
	ErrorInfo(const string& info, const ErrType& type) :
			_info(info), _type(type) {
	}

	string& Info() const {
		return _info;
	}

	ErrType& ErrType() const {
		return _type;
	}
private:
	string _info;
	ErrType _type;
};

template<typename T>
struct Result {
	Result(const T& e) :
			_f([=](T& e_)->bool {e_ = e;return false;}) {
	}
	Result() :
			_f([=](T&)->bool {return true;}) {
	}

	bool operator()(T& e) {
		return _f(e);
	}
private:
	function<bool(T&)> _f;
};

} /* namespace Util */

#endif /* UTIL_RESULT_H_ */
