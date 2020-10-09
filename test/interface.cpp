/*
 * interface.cpp
 *
 *  Created on: Aug 24, 2020
 *      Author: bflynt
 */

#include "json.hpp"

int main() {

	//
	// Current Interface
	//
	auto main_obj = json::parse_file("data/input.jsn");

	auto sub_obj  = main_obj["object_1"];

	//auto age = json::get<int>( sub_obj["age"] );

	//auto val = json::get<double>( main_obj["2D Array"][0][0] );

	auto real_array_value   = main_obj["2D Array"][0][0].get<float>();

	auto real_array_value_2 = json::get<float>(main_obj["2D Array"][0][0]);

	auto string_array_value = json::get(main_obj["2D Array"][0][0], std::string("Hello"));

	//int age = json::value_cast<int>( main_obj["object_1"]["age"] );


	return 0;
}


