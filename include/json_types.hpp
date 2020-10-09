/*
 * json_types.hpp
 *
 *  Created on: Aug 13, 2020
 *      Author: bflynt
 */

#ifndef JSON_ST_HPP_
#define JSON_ST_HPP_


#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

#include <iostream>


namespace json {
	class Value;

	namespace types {
		using Array   = std::vector<Value>;
		using Boolean = bool;
		using Integer = std::int64_t;
		using Object  = std::map<std::string, Value>;
		using Real    = long double;
		using String  = std::string;
	} /* namespace type */

} /* namespace json */


namespace json {

    /** A JSON value. Can have either type in ValueTypes. */
    class Value {
    public:

    	using size_type = typename types::Array::size_type;

        /** Default constructor (type = NIL). */
        Value();

        /** Copy constructor. */
        Value(const Value& v);

        /** Constructor from int. */
        Value(const types::Integer i);

        /** Constructor from float. */
        Value(const types::Real f);

        /** Constructor from bool. */
        Value(const types::Boolean b);

        /** Constructor from pointer to char (C-string).  */
        Value(const char* s);

        /** Constructor from STD string  */
        Value(const types::String& s);

        /** Constructor from pointer to Object. */
        Value(const types::Object& o);

        /** Constructor from pointer to Array. */
        Value(const types::Array& a);

        /** Move constructor. */
        Value(Value&& v);

        /** Move constructor from STD string  */
        Value(types::String&& s);

        /** Move constructor from pointer to Object. */
        Value(types::Object&& o);

        /** Move constructor from pointer to Array. */
        Value(types::Array&& a);

        /** Type query. */
        const std::type_info& type() const {
            return value_.type();
        }

        /** Subscript operator, access an element by key.
            @param key key of the object to access
        */
        Value& operator[](const std::string& key);

        /** Subscript operator, access an element by index.
            @param i index of the element to access
        */
        Value& operator[](const size_type i);

        /** Subscript operator, access an element by index.
            @param i index of the element to access
        */
        const Value& operator[](const size_type i) const;

        /** Assignment operator. */
        Value& operator=(const Value& v);

        /** Move operator. */
        Value& operator=(Value&& v);

        /** Cast operator for float */
        explicit operator types::Real() const { return std::any_cast<types::Real>(value_); }

        /** Cast operator for int */
        explicit operator types::Integer() const { return std::any_cast<types::Integer>(value_); }

        /** Cast operator for bool */
        explicit operator types::Boolean() const { return std::any_cast<types::Boolean>(value_); }

        /** Cast operator for string */
        explicit operator types::String () const { return std::any_cast<types::String>(value_); }

        /** Cast operator for Object */
        operator types::Object () const { return std::any_cast<types::Object>(value_); }

        /** Cast operator for Object */
        operator types::Array () const { return std::any_cast<types::Array>(value_); }

        template<typename T>
        T get() const;

        template<typename T>
        T get(const T& default_value) const;

    protected:
        std::any	value_;
    };

} /* namespace json */

/** Output operator for Values */
std::ostream& operator<<(std::ostream&, const json::Value&);



namespace json {

template<typename T>
T
Value::get() const {
	T answer;

	// Requesting Boolean
	// - Accepts:
	// --- Boolean value
	// --- Integer of 0 or 1
	if constexpr (std::is_same_v<T,types::Boolean>) {
	    if( this->type() == typeid(types::Boolean) ){
	    	answer = std::any_cast<types::Boolean>(value_);
	    }
	    else if( this->type() == typeid(types::Integer) ){
	    	auto ival = std::any_cast<types::Integer>(value_);
	    	if( (0 != ival) and (1 != ival) ){
	    		throw std::logic_error("Boolean Value is Integer besides 0 or 1");
	    	}
	    	answer = ival;
	    }
	    else {
	    	throw std::logic_error("Value not a Boolean");
	    }
	}

	// Requesting Integer
	// - Accepts:
	// --- Integer value
	// --- Real value without loss
	else if constexpr (std::is_integral_v<T>) {
		if( this->type() == typeid(types::Integer) ){
			answer = std::any_cast<types::Integer>(value_);
		}
		else if( this->type() == typeid(types::Real) ){
			auto rval = std::any_cast<types::Real>(value_);
			answer = rval;
			if( rval != static_cast<types::Real>(answer) ){
				 throw std::logic_error("Floating Point cannot be Truncated to Integer");
			}
		}
		else {
			throw std::logic_error("Value not a Integer");
		}
	}

	// Requesting Real
	// - Accepts:
	// --- Real value
	// --- Integer value
	else if constexpr (std::is_floating_point_v<T>) {
		if( this->type() == typeid(types::Real) ) {
			answer = std::any_cast<types::Real>(value_);
		}
		else if( this->type() == typeid(types::Integer) ) {
			answer = std::any_cast<types::Integer>(value_);
		}
		else {
			throw std::logic_error("Value not Floating Point");
		}
	}

	// Requesting String
	// - Accepts:
	// --- String value
	else if constexpr (std::is_same_v<T,std::string>) {
		if( this->type() == typeid(types::String) ) {
			answer = std::any_cast<types::String>(value_);
		}
		else {
			throw std::logic_error("Value not String");
		}
	}

	// Requesting Unknown Type
	else {
		throw std::logic_error("Requested Type is Not Recognized");
	}

	return answer;
}

template<typename T>
T
Value::get(const T& default_value) const {
	T answer = default_value;

		// Requesting Boolean
		// - Accepts:
		// --- Boolean value
		// --- Integer of 0 or 1
		if constexpr (std::is_same_v<T,types::Boolean>) {
		    if( this->type() == typeid(types::Boolean) ){
		    	answer = std::any_cast<types::Boolean>(value_);
		    }
		    else if( this->type() == typeid(types::Integer) ){
		    	auto ival = std::any_cast<types::Integer>(value_);
		    	if( (0 == ival) or (1 == ival) ){
		    		answer = ival;
		    	}
		    }
		}

		// Requesting Integer
		// - Accepts:
		// --- Integer value
		// --- Real value without loss
		else if constexpr (std::is_integral_v<T>) {
			if( this->type() == typeid(types::Integer) ){
				answer = std::any_cast<types::Integer>(value_);
			}
			else if( this->type() == typeid(types::Real) ){
				auto real_val = std::any_cast<types::Real>(value_);
				T    cast_val = static_cast<T>(real_val);
				if( real_val == static_cast<types::Real>(cast_val) ){
					answer = cast_val;
				}
			}
		}

		// Requesting Real
		// - Accepts:
		// --- Real value
		// --- Integer value
		else if constexpr (std::is_floating_point_v<T>) {
			if( this->type() == typeid(types::Real) ) {
				answer = std::any_cast<types::Real>(value_);
			}
			else if( this->type() == typeid(types::Integer) ) {
				answer = std::any_cast<types::Integer>(value_);
			}
		}

		// Requesting String
		// - Accepts:
		// --- String value
		else if constexpr (std::is_same_v<T,std::string>) {
			if( this->type() == typeid(types::String) ) {
				answer = std::any_cast<types::String>(value_);
			}
		}

		// Requesting Unknown Type
		else {
			throw std::logic_error("Requested Type is Not Recognized");
		}

		return answer;
}





} /* namespace json */

#endif /* JSON_ST_HPP_ */
