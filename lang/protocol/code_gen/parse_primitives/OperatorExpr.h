//
// Created by skod on 12/14/21.
//

#ifndef PROTOCOL_COMPILER_OPERATOREXPR_H
#define PROTOCOL_COMPILER_OPERATOREXPR_H

#include "lang/protocol/Tokens.h"
#include "Expression.h"

#include <string>
#include <unordered_map>

class ClassVisitor;

class OperatorExpr : public Expression {

    std::string value;

    Expression* left_expr;
    Expression* right_expr;

    static const std::unordered_map<std::string, std::string> symbol_to_op;

public:

    OperatorExpr(const std::string& value, Expression* lhs, Expression* rhs);

    std::string get_operator() const;

    Expression* get_left_expr() const;

    Expression* get_right_expr() const;

    virtual void visit(ClassVisitor* visitor) const;

};




#endif //PROTOCOL_COMPILER_OPERATOREXPR_H
