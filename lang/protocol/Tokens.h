//
// Created by skod on 14/06/2021.
//

#ifndef PARSER_TOKENS_H
#define PARSER_TOKENS_H

#include "../../GrammarToken.h"

namespace ProtocolParser {

    class Tokens {

    public:

        // lexer tokens
        static const std::string FIELD;
        static const std::string PROTOCOL;
        static const std::string ENUM;
        static const std::string BITMAP;
        static const std::string CONDITIONAL;
        static const std::string LEFT_PAR;
        static const std::string RIGHT_PAR;
        static const std::string DASH;
        static const std::string COMMA;
        static const std::string PLUS;
        static const std::string MUL;
        static const std::string ID;
        static const std::string INT;

        // grammar tokens
        static const GrammarToken START_TOKEN;
        static const GrammarToken EPS_TOKEN;
        static const GrammarToken DEF_TOKEN;
        static const GrammarToken PRO_TOKEN;
        static const GrammarToken TER_TOKEN;
        static const GrammarToken EXPR_TOKEN;
        static const GrammarToken VAR_TOKEN;
        static const GrammarToken EXPR_1_TOKEN;
        static const GrammarToken OP_TOKEN;
        static const GrammarToken STMT_TOKEN;
        static const GrammarToken BITMAP_TOKEN;
        static const GrammarToken ENUM_TOKEN;
        static const GrammarToken ID_VAL_TUPLE_TOKEN;
        static const GrammarToken ID_VAL_TUPLE_1_TOKEN;
        static const GrammarToken COND_TOKEN;
        static const GrammarToken COND_FUN_TOKEN;
        static const GrammarToken ARG_LIST_TOKEN;
        static const GrammarToken ARG_LIST_1_TOKEN;
        static const GrammarToken ID_TOKEN;
        static const GrammarToken INT_TOKEN;
        static const GrammarToken PLUS_TOKEN;
        static const GrammarToken LEFT_PAR_TOKEN;
        static const GrammarToken RIGHT_PAR_TOKEN;
        static const GrammarToken MUL_TOKEN;
        static const GrammarToken DASH_TOKEN;
        static const GrammarToken PROTOCOL_TOKEN;
        static const GrammarToken FIELD_TOKEN;
        static const GrammarToken COMMA_TOKEN;
        static const GrammarToken BITMAP_TOKEN_T;
        static const GrammarToken ENUM_TOKEN_T;
        static const GrammarToken COND_TOKEN_T;


    };

const std::string Tokens::FIELD = "FIELD";
const std::string Tokens::PROTOCOL = "PROTOCOL";
const std::string Tokens::ENUM = "ENUM";
const std::string Tokens::BITMAP = "BITMAP";
const std::string Tokens::CONDITIONAL = "CONDITIONAL";
const std::string Tokens::LEFT_PAR = "LEFT_PAR";
const std::string Tokens::RIGHT_PAR = "RIGHT_PAR";
const std::string Tokens::DASH = "DASH";
const std::string Tokens::COMMA = "COMMA";
const std::string Tokens::PLUS = "PLUS";
const std::string Tokens::MUL = "MUL";
const std::string Tokens::ID = "ID";
const std::string Tokens::INT = "INT";

const GrammarToken Tokens::START_TOKEN = Grammar<Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>>::START;
const GrammarToken Tokens::EPS_TOKEN = Grammar<Production<GrammarToken, void (*)(std::deque<ParserAction<Node*>>&)>>::EPSILON;
const GrammarToken Tokens::DEF_TOKEN("NON_TERM", "DEFINITION", false);
const GrammarToken Tokens::PRO_TOKEN("NON_TERM", "PROTOCOL", false);
const GrammarToken Tokens::TER_TOKEN("NON_TERM", "TERMINATION", false);
const GrammarToken Tokens::EXPR_TOKEN("NON_TERM", "EXPR", false);
const GrammarToken Tokens::VAR_TOKEN("NON_TERM", "VAR", false);
const GrammarToken Tokens::EXPR_1_TOKEN("NON_TERM", "EXPR_1", false);
const GrammarToken Tokens::OP_TOKEN("NON_TERM", "OP", false);
const GrammarToken Tokens::STMT_TOKEN("NON_TERM", "STMT", false);
const GrammarToken Tokens::BITMAP_TOKEN("NON_TERM", "BITMAP", false);
const GrammarToken Tokens::ENUM_TOKEN("NON_TERM", "ENUM", false);
const GrammarToken Tokens::ID_VAL_TUPLE_TOKEN("NON_TERM", "ID_VAL_TUPLE", false);
const GrammarToken Tokens::ID_VAL_TUPLE_1_TOKEN("NON_TERM", "ID_VAL_TUPLE_1", false);
const GrammarToken Tokens::COND_TOKEN("NON_TERM", "COND_TOKEN", false);
const GrammarToken Tokens::COND_FUN_TOKEN("NON_TERM", "COND_FUN_TOKEN", false);
const GrammarToken Tokens::ARG_LIST_TOKEN("NON_TERM", "ARG_LIST_TOKEN", false);
const GrammarToken Tokens::ARG_LIST_1_TOKEN("NON_TERM", "ARG_LIST_1_TOKEN", false);

const GrammarToken Tokens::ID_TOKEN("TERM", Tokens::ID, true, std::regex("[a-zA-Z_]+"));
const GrammarToken Tokens::INT_TOKEN("TERM", Tokens::INT, true, std::regex("\\d+"));
const GrammarToken Tokens::PLUS_TOKEN("TERM", Tokens::PLUS, true);
const GrammarToken Tokens::LEFT_PAR_TOKEN("TERM", Tokens::LEFT_PAR, true);
const GrammarToken Tokens::RIGHT_PAR_TOKEN("TERM", Tokens::RIGHT_PAR, true);
const GrammarToken Tokens::MUL_TOKEN("TERM", Tokens::MUL, true);
const GrammarToken Tokens::DASH_TOKEN("TERM", Tokens::DASH, true);
const GrammarToken Tokens::PROTOCOL_TOKEN("TERM", Tokens::PROTOCOL, true);
const GrammarToken Tokens::FIELD_TOKEN("TERM", Tokens::FIELD, true);
const GrammarToken Tokens::COMMA_TOKEN("TERM", Tokens::COMMA, true);
const GrammarToken Tokens::BITMAP_TOKEN_T("TERM", Tokens::BITMAP, true);
const GrammarToken Tokens::ENUM_TOKEN_T("TERM", Tokens::ENUM, true);
const GrammarToken Tokens::COND_TOKEN_T("TERM", Tokens::CONDITIONAL, true);

}


#endif //PARSER_TOKENS_H
