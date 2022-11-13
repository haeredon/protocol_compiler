//
// Created by skod on 12/14/21.
//

#include "OperatorExpr.h"

OperatorExpr::OperatorExpr(const std::string& value, Expression* lhs, Expression* rhs): Expression(), value(value), left_expr(lhs), right_expr(rhs) {

}


std::string OperatorExpr::to_string() const {
    return OperatorExpr::symbol_to_op.at(value);
}


const std::unordered_map<std::string , std::string> OperatorExpr::symbol_to_op = {
        std::pair<std::string, std::string>(ProtocolParser::Tokens::PLUS, "+"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::MINUS, "-"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::LESS_THAN, "<"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::GREATER_THAN, ">"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::AND, "&"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::OR, "|")
};