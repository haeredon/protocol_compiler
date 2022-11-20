//
// Created by skod on 14/06/2021.
//

#ifndef PARSER_LEXERDEFS_H
#define PARSER_LEXERDEFS_H

#include "Tokens.h"


namespace ProtocolParser {

    class LexerDefs {

    public:

        static const std::vector<std::pair<std::regex, std::string>> REG_TOKEN;

    };

    const std::vector<std::pair<std::regex, std::string>> LexerDefs::REG_TOKEN = {
            std::pair<std::regex, std::string>(std::regex("field:"), Tokens::FIELD),
            std::pair<std::regex, std::string>(std::regex("protocol:"), Tokens::PROTOCOL),
            std::pair<std::regex, std::string>(std::regex("next_protocol:"), Tokens::NEXT_PROTOCOL),
            std::pair<std::regex, std::string>(std::regex("while:"), Tokens::WHILE),
            std::pair<std::regex, std::string>(std::regex("switch:"), Tokens::SWITCH),
            std::pair<std::regex, std::string>(std::regex("end:"), Tokens::END),
            std::pair<std::regex, std::string>(std::regex("enum:"), Tokens::ENUM),
            std::pair<std::regex, std::string>(std::regex("bitmap:"), Tokens::BITMAP),
            std::pair<std::regex, std::string>(std::regex("inner:"), Tokens::INNER),
            std::pair<std::regex, std::string>(std::regex(":"), Tokens::COLON),
            std::pair<std::regex, std::string>(std::regex("&&"), Tokens::AND),
            std::pair<std::regex, std::string>(std::regex("\\|\\|"), Tokens::OR),
            std::pair<std::regex, std::string>(std::regex(">"), Tokens::GREATER_THAN),
            std::pair<std::regex, std::string>(std::regex("<"), Tokens::LESS_THAN),
            std::pair<std::regex, std::string>(std::regex("\"[^\"]+\""), Tokens::STRING),
            std::pair<std::regex, std::string>(std::regex("range_equals|equals|has_not|lte|gt|prefix|cdata"), Tokens::CONDITIONAL),
            std::pair<std::regex, std::string>(std::regex("\\("), Tokens::LEFT_PAR),
            std::pair<std::regex, std::string>(std::regex("\\)"), Tokens::RIGHT_PAR),
            std::pair<std::regex, std::string>(std::regex("\\."), Tokens::DOT),
            std::pair<std::regex, std::string>(std::regex("#"), Tokens::DASH),
            std::pair<std::regex, std::string>(std::regex("[a-zA-Z_]+[a-zA-Z_0-9]*"), Tokens::ID),
            std::pair<std::regex, std::string>(std::regex(","), Tokens::COMMA),
            std::pair<std::regex, std::string>(std::regex("\\+"), Tokens::PLUS),
            std::pair<std::regex, std::string>(std::regex("\\d+"), Tokens::INT),
            std::pair<std::regex, std::string>(std::regex("-"), Tokens::MINUS)
    };



}

#endif //PARSER_LEXERDEFS_H
