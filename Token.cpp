#include "Token.h"


namespace ProtocolParser {

    Token::Token(std::string tag, std::string value) : tag(tag), value(value) {
    }


    std::string Token::get_value() const {
        return value;
    }

    std::string Token::get_tag() const {
        return tag;
    }

    bool Token::operator==(const Token &other) const {
        return value == other.value && tag == other.tag;
    }

    bool Token::operator<(const Token &other) const {
        return value < other.value;
    }







}