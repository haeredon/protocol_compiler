//
// Created by skod on 14/06/2021.
//

#ifndef PARSER_TOKENS_H
#define PARSER_TOKENS_H

#include "../../GrammarToken.h"
#include "../../Production.h"
#include "../../Grammar.h"

#include <unordered_map>

namespace ProtocolParser {

    class Tokens {

    public:

        // lexer tokens
        static const std::string FIELD;
        static const std::string PROTOCOL;
        static const std::string NEXT_PROTOCOL;
        static const std::string FIELD_GROUP;
        static const std::string ENUM;
        static const std::string BITMAP;
        static const std::string INNER;
        static const std::string CONDITIONAL;
        static const std::string LEFT_PAR;
        static const std::string RIGHT_PAR;
        static const std::string DOT;
        static const std::string DASH;
        static const std::string COMMA;
        static const std::string PLUS;
        static const std::string MINUS;
        static const std::string AND;
        static const std::string OR;
        static const std::string LESS_THAN;
        static const std::string GREATER_THAN;
        static const std::string ID;
        static const std::string INT;
        static const std::string END;
        static const std::string STRING;

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
        static const GrammarToken FUN_TOKEN;
        static const GrammarToken STMT_1_TOKEN;
        static const GrammarToken STMT_2_TOKEN;
        static const GrammarToken STRING_TOKEN;
        static const GrammarToken FIELD_GROUP_TOKEN;
        static const GrammarToken BITMAP_TOKEN;
        static const GrammarToken INNER_TOKEN;
        static const GrammarToken ENUM_TOKEN;
        static const GrammarToken ID_VAL_TUPLE_TOKEN;
        static const GrammarToken ID_VAL_TUPLE_1_TOKEN;
        static const GrammarToken OPTIONAL_TOKEN;
        static const GrammarToken COND_FUN_TOKEN;
        static const GrammarToken ARG_LIST_TOKEN;
        static const GrammarToken ARG_LIST_1_TOKEN;
        static const GrammarToken ID_TOKEN;
        static const GrammarToken INT_TOKEN;
        static const GrammarToken PLUS_TOKEN;
        static const GrammarToken LEFT_PAR_TOKEN;
        static const GrammarToken RIGHT_PAR_TOKEN;
        static const GrammarToken MINUS_TOKEN;
        static const GrammarToken DASH_TOKEN;
        static const GrammarToken PROTOCOL_TOKEN;
        static const GrammarToken NEXT_PROTOCOL_TOKEN;
        static const GrammarToken FIELD_TOKEN;
        static const GrammarToken COMMA_TOKEN;
        static const GrammarToken BITMAP_TOKEN_T;
        static const GrammarToken INNER_TOKEN_T;
        static const GrammarToken ENUM_TOKEN_T;
        static const GrammarToken COND_TOKEN_T;
        static const GrammarToken FIELD_GROUP_TOKEN_T;
        static const GrammarToken END_TOKEN;
        static const GrammarToken DOT_TOKEN;
        static const GrammarToken DOT_EXPR_TOKEN;
        static const GrammarToken AND_TOKEN;
        static const GrammarToken OR_TOKEN;
        static const GrammarToken LESS_THAN_TOKEN;
        static const GrammarToken GREATER_THAN_TOKEN;
        static const GrammarToken QUOTE_TOKEN;
        static const GrammarToken STRING_TOKEN_T;

        static const std::unordered_map<std::string , short> op_precedence;

    };


}


#endif //PARSER_TOKENS_H
