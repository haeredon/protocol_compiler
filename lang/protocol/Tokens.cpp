//
// Created by skod on 12/27/21.
//

#include "Tokens.h"

namespace ProtocolParser {


    const std::string Tokens::FIELD = "FIELD";
    const std::string Tokens::PROTOCOL = "PROTOCOL";
    const std::string Tokens::NEXT_PROTOCOL = "NEXT_PROTOCOL";
    const std::string Tokens::FIELD_GROUP = "FIELD_GROUP";
    const std::string Tokens::ENUM = "ENUM";
    const std::string Tokens::BITMAP = "BITMAP";
    const std::string Tokens::INNER = "INNER";
    const std::string Tokens::CONDITIONAL = "CONDITIONAL";
    const std::string Tokens::LEFT_PAR = "LEFT_PAR";
    const std::string Tokens::RIGHT_PAR = "RIGHT_PAR";
    const std::string Tokens::DOT = "DOT";
    const std::string Tokens::DASH = "DASH";
    const std::string Tokens::COMMA = "COMMA";
    const std::string Tokens::PLUS = "PLUS";
    const std::string Tokens::MINUS = "MINUS";
    const std::string Tokens::ID = "ID";
    const std::string Tokens::INT = "INT";
    const std::string Tokens::END = "END";
    const std::string Tokens::OR = "OR";
    const std::string Tokens::LESS_THAN = "LESS_THAN";
    const std::string Tokens::GREATER_THAN = "GREATER_THAN";
    const std::string Tokens::AND = "AND";
    const std::string Tokens::STRING = "STRING";


    const GrammarToken Tokens::START_TOKEN = Grammar<Production<GrammarToken, void (*)(
            std::deque<ParserAction<Node *>> &)>>::START;
    const GrammarToken Tokens::EPS_TOKEN = Grammar<Production<GrammarToken, void (*)(
            std::deque<ParserAction<Node *>> &)>>::EPSILON;
    const GrammarToken Tokens::DEF_TOKEN("NON_TERM", "DEFINITION", false);
    const GrammarToken Tokens::PRO_TOKEN("NON_TERM", "PROTOCOL", false);
    const GrammarToken Tokens::TER_TOKEN("NON_TERM", "TERMINATION", false);
    const GrammarToken Tokens::EXPR_TOKEN("NON_TERM", "EXPR", false);
    const GrammarToken Tokens::VAR_TOKEN("NON_TERM", "VAR", false);
    const GrammarToken Tokens::EXPR_1_TOKEN("NON_TERM", "EXPR_1", false);
    const GrammarToken Tokens::OP_TOKEN("NON_TERM", "OP", false);
    const GrammarToken Tokens::STMT_1_TOKEN("NON_TERM", "STMT_1", false);
    const GrammarToken Tokens::STMT_2_TOKEN("NON_TERM", "STMT_2", false);
    const GrammarToken Tokens::BITMAP_TOKEN("NON_TERM", "BITMAP", false);
    const GrammarToken Tokens::INNER_TOKEN("NON_TERM", "INNER", false);
    const GrammarToken Tokens::FUN_TOKEN("NON_TERM", "FUN", false);
    const GrammarToken Tokens::ENUM_TOKEN("NON_TERM", "ENUM", false);
    const GrammarToken Tokens::ID_VAL_TUPLE_TOKEN("NON_TERM", "ID_VAL_TUPLE", false);
    const GrammarToken Tokens::ID_VAL_TUPLE_1_TOKEN("NON_TERM", "ID_VAL_TUPLE_1", false);
    const GrammarToken Tokens::OPTIONAL_TOKEN("NON_TERM", "OPTIONAL_TOKEN", false);
    const GrammarToken Tokens::COND_FUN_TOKEN("NON_TERM", "COND_FUN_TOKEN", false);
    const GrammarToken Tokens::ARG_LIST_TOKEN("NON_TERM", "ARG_LIST_TOKEN", false);
    const GrammarToken Tokens::ARG_LIST_1_TOKEN("NON_TERM", "ARG_LIST_1_TOKEN", false);
    const GrammarToken Tokens::DOT_EXPR_TOKEN("NON_TERM", "DOT_EXPR_TOKEN", false);
    const GrammarToken Tokens::FIELD_GROUP_TOKEN("TERM", "FIELD_GROUP_TOKEN", false);
    const GrammarToken Tokens::STRING_TOKEN("TERM", "STRING_TOKEN", false);

    const GrammarToken Tokens::ID_TOKEN("TERM", Tokens::ID, true, std::regex("[a-zA-Z_]+[a-zA-Z_0-9]*"));
    const GrammarToken Tokens::INT_TOKEN("TERM", Tokens::INT, true, std::regex("\\d+"));
    const GrammarToken Tokens::PLUS_TOKEN("TERM", Tokens::PLUS, true);
    const GrammarToken Tokens::LEFT_PAR_TOKEN("TERM", Tokens::LEFT_PAR, true);
    const GrammarToken Tokens::RIGHT_PAR_TOKEN("TERM", Tokens::RIGHT_PAR, true);
    const GrammarToken Tokens::MINUS_TOKEN("TERM", Tokens::MINUS, true);
    const GrammarToken Tokens::DASH_TOKEN("TERM", Tokens::DASH, true);
    const GrammarToken Tokens::PROTOCOL_TOKEN("TERM", Tokens::PROTOCOL, true);
    const GrammarToken Tokens::NEXT_PROTOCOL_TOKEN("TERM", Tokens::NEXT_PROTOCOL, true);
    const GrammarToken Tokens::FIELD_TOKEN("TERM", Tokens::FIELD, true);
    const GrammarToken Tokens::COMMA_TOKEN("TERM", Tokens::COMMA, true);
    const GrammarToken Tokens::BITMAP_TOKEN_T("TERM", Tokens::BITMAP, true);
    const GrammarToken Tokens::INNER_TOKEN_T("TERM", Tokens::INNER, true);
    const GrammarToken Tokens::ENUM_TOKEN_T("TERM", Tokens::ENUM, true);
    const GrammarToken Tokens::COND_TOKEN_T("TERM", Tokens::CONDITIONAL, true);
    const GrammarToken Tokens::END_TOKEN("TERM", Tokens::END, true);
    const GrammarToken Tokens::FIELD_GROUP_TOKEN_T("TERM", Tokens::FIELD_GROUP, true);
    const GrammarToken Tokens::DOT_TOKEN("TERM", Tokens::DOT, true);
    const GrammarToken Tokens::AND_TOKEN("TERM", Tokens::AND, true);
    const GrammarToken Tokens::OR_TOKEN("TERM", Tokens::OR, true);
    const GrammarToken Tokens::LESS_THAN_TOKEN("TERM", Tokens::LESS_THAN, true);
    const GrammarToken Tokens::GREATER_THAN_TOKEN("TERM", Tokens::GREATER_THAN, true);
    const GrammarToken Tokens::STRING_TOKEN_T("TERM", Tokens::STRING, true, std::regex("[a-zA-Z_]+[a-zA-Z_0-9]*"));

    const std::unordered_map<std::string, short> Tokens::op_precedence = {
            std::pair<std::string, short>(Tokens::PLUS, 9),
            std::pair<std::string, short>(Tokens::MINUS, 9),
            std::pair<std::string, short>(Tokens::LESS_THAN, 8),
            std::pair<std::string, short>(Tokens::GREATER_THAN, 8),
            std::pair<std::string, short>(Tokens::AND, 5),
            std::pair<std::string, short>(Tokens::OR, 5)
    };

}