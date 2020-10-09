/*
 * unescape.hh
 *
 *  Created on: Aug 13, 2020
 *      Author: bflynt
 */

#ifndef UNESCAPE_HPP_
#define UNESCAPE_HPP_

#include <stdexcept>
#include <string>

#include "code_point_to_utf8.hpp"

namespace json {

    namespace HELPER {

        inline void unescape(std::string& s)
        {
            std::string result;

            auto citer = s.cbegin();
            while (citer != s.cend()) {
                const auto c = *citer++;
                if (c == '\\') {
                    switch (*citer++) {
                    case '"': result += '\"'; break;
                    case '\\': result += '\\'; break;
                    case '/': result += '/'; break;
                    case 'b': result += '\b'; break;
                    case 'f': result += '\f'; break;
                    case 'n': result += '\n'; break;
                    case 't': result += '\t'; break;
                    case 'r': result += '\r'; break;
                    case 'u': {
                            const std::string code_point_str { citer, citer + 4 };
                            const char16_t code_point {
                                static_cast<char16_t>(std::stoul(code_point_str, 0, 16)) };
                            result += code_point_to_utf8(code_point);
                            std::advance(citer, 4);
                            break;
                        }
                    default:
                        throw std::runtime_error("Unexpected escape character in " + s);
                    }
                }
                else {
                    result += c;
                }
            }

            s = std::move(result);
        }
    }
}



#endif /* UNESCAPE_HPP_ */
