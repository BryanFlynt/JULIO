/*
 * json_st.cpp
 *
 *  Created on: Aug 13, 2020
 *      Author: bflynt
 */




#include <stdexcept>
#include <string>
#include "../include/json_types.hpp"


namespace json {

Value::Value() { }

Value::Value(const types::Integer i) : value_(i) { }

Value::Value(const types::Real f) : value_(f) { }

Value::Value(const types::Boolean b) : value_(b) { }

Value::Value(const char* s) : value_(s) { }

Value::Value(const types::String& s) : value_(s) { }

Value::Value(const types::Object& o) : value_(o) { }

Value::Value(const types::Array& a) : value_(a) { }

Value::Value(types::String&& s) : value_(std::move(s)) { }

Value::Value(types::Object&& o) : value_(std::move(o)) { }

Value::Value(types::Array&& a) : value_(std::move(a)) { }

Value::Value(const Value& v) : value_(v.value_) { }

Value::Value(Value&& v) :  value_(std::move(v.value_)) { }

Value& Value::operator=(const Value& v) {
	value_ = v.value_;
	return *this;
}

Value& Value::operator=(Value&& v) {
	value_ = std::move(v.value_);
    return *this;
}

Value& Value::operator[] (const std::string& key) {
    if( value_.type() != typeid(types::Object) )
        throw std::logic_error("Value not an object");
    return std::any_cast<types::Object&>(value_)[key];
}

Value& Value::operator[] (const std::size_t i) {
    if( value_.type() != typeid(types::Array) )
        throw std::logic_error("Value not an array");
    return std::any_cast<types::Array&>(value_)[i];
}

const Value& Value::operator[] (const std::size_t i) const {
    if( value_.type() != typeid(types::Array) )
        throw std::logic_error("Value not an array");
    return std::any_cast<const types::Array&>(value_)[i];
}


} /* namespace json */

std::ostream& operator<<(std::ostream& os, const json::Value& v) {

	if( v.type() == typeid(void) ){
		os << "null";
	}
	else if( v.type() == typeid(json::types::Boolean) ){
		os << ((bool)v ? "true" : "false");
	}
	else if(v.type() == typeid(json::types::Integer)){
		os << static_cast<json::types::Integer>(v);
	}
	else if(v.type() == typeid(json::types::Real)){
		os << (json::types::Real)v;
	}
	else if(v.type() == typeid(json::types::String)){
		os << '"' << (json::types::String)v << '"';
	}
	else if(v.type() == typeid(json::types::Array)){
		os << (json::types::Array)v;
	}
	else if(v.type() == typeid(json::types::Object)){
		os << (json::types::Object)v;
	}
	else{
		throw std::logic_error("Value holding unrecognized Type");
	}
    return os;
}


