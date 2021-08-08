#include "LexerToken.h"


namespace ProtocolParser {

    LexerToken::LexerToken(std::string type, std::string value, std::size_t position) : Token(type, value), position(position) {
    }



}