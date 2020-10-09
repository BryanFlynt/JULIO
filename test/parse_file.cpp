/*
 * test.cpp
 *
 *  Created on: Aug 13, 2020
 *      Author: bflynt
 */
#include "json.hpp"
using namespace json;

int main() {

	auto obj = parse_file("data/generated.jsn");

    return 0;
}
