//
// Created by skod on 12/14/21.
//

#include "OperatorExpr.h"

OperatorExpr::OperatorExpr(const std::string& value, Expression* lhs, Expression* rhs): Expression(), value(value), left_expr(lhs), right_expr(rhs) {

}


std::string OperatorExpr::to_string() const {
    std::stringstream ss;

    ss << left_expr->to_string();
    ss << OperatorExpr::symbol_to_op.at(value);
    ss << right_expr->to_string();

    return ss.str();
}

const std::unordered_map<std::string , std::string> OperatorExpr::symbol_to_op = {
        std::pair<std::string, std::string>(ProtocolParser::Tokens::PLUS, "+"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::MINUS, "-"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::LESS_THAN, "<"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::GREATER_THAN, ">"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::AND, "&"),
        std::pair<std::string, std::string>(ProtocolParser::Tokens::OR, "|")
};


std::endian OperatorExpr::get_endianness() {
    return std::endian::little;
}


//template<class NUM_T>
//static bool less_than(NUM_T little_endian, NUM_T big_endian) {
//    less_greater_compare<NUM_T, less>(little_endian, big_endian);
//}
//
//template<class NUM_T>
//static bool greater_than(NUM_T little_endian, NUM_T big_endian) {
//    less_greater_compare<NUM_T, greater>(little_endian, big_endian);
//}