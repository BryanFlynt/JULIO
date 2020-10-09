/*
 * get.hpp
 *
 *  Created on: Aug 24, 2020
 *      Author: bflynt
 */

#ifndef INCLUDE_GET_HPP_
#define INCLUDE_GET_HPP_

#include "json_types.hpp"

namespace json {

template<typename T>
T
get(const Value& value) {
	return value.get<T>();
}


template<typename T>
T
get(const Value& value, const T& default_value) {
	return value.get(default_value);
}

} /* namespace json */

#endif /* INCLUDE_GET_HPP_ */
