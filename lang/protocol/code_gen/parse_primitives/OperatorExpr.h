//
// Created by skod on 12/14/21.
//

#ifndef PROTOCOL_COMPILER_OPERATOREXPR_H
#define PROTOCOL_COMPILER_OPERATOREXPR_H

#include "lang/protocol/Tokens.h"
#include "Expression.h"

#include <string>
#include <unordered_map>


class OperatorExpr : public Expression {

    std::string value;

    Expression* left_expr;
    Expression* right_expr;

    static const std::unordered_map<std::string, std::string> symbol_to_op;

public:

    OperatorExpr(const std::string& value, Expression* lhs, Expression* rhs);

    std::string to_string() const;

    std::endian get_endianness();
};




#endif //PROTOCOL_COMPILER_OPERATOREXPR_H
