//
// Created by skod on 12/14/21.
//

#include "OperatorExpr.h"

OperatorExpr::OperatorExpr(const std::string &value) : value(value) {

}


std::string OperatorExpr::to_string() {
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