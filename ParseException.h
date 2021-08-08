//
// Created by root on 08/08/2021.
//

#ifndef PROTOCOL_COMPILER_PARSEEXCEPTION_H
#define PROTOCOL_COMPILER_PARSEEXCEPTION_H

#include <string>

namespace ProtocolParser {

    template<class LEXER_TOKEN_T>
    class ParseException : public std::exception {

        const LEXER_TOKEN_T lexer_token;
        const std::string info;


    public:
        ParseException(const LEXER_TOKEN_T& lexer_token, const std::string& info = "") : lexer_token(lexer_token), info(info) {}

        const LEXER_TOKEN_T get_lexer_token() const {
            return lexer_token;
        }

        const std::string get_info() const {
            return info;
        }

    };

}

#endif //PROTOCOL_COMPILER_PARSEEXCEPTION_H
