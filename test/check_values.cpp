/*
 * check_values.cpp
 *
 *  Created on: Aug 17, 2020
 *      Author: bflynt
 */

#include "json.hpp"
using namespace json;

int main() {

    // Load JSON file
	auto main_obj = parse_file("data/input.jsn");

	long double real_value = (long double) main_obj["real_value"];
	std::cout << real_value << std::endl;

	//int age = json::value_cast<int>( main_obj["object_1"]["age"] );


	return 0;
}
