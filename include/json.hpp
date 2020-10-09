/*
 * json.hpp
 *
 *  Created on: Aug 13, 2020
 *      Author: bflynt
 */

#ifndef JSON_HPP_
#define JSON_HPP_


#include "json.tab.hpp"    // parser
#include "json_types.hpp"  // JSON syntax tree
#include "get.hpp"         // JSON syntax tree

namespace json {

Value parse_file(const char* filename);
Value parse_string(const std::string& s);

} /* namespace json */

#endif /* JSON_HPP_ */
