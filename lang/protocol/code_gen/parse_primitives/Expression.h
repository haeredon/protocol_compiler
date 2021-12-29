//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_EXPRESSION_H
#define PROTOCOL_COMPILER_EXPRESSION_H

#include "ExpressionHandler.h"

#include <string>
#include <functional>

class Expression {


    ExpressionHandler* expr_element;
    Expression* left_expr;
    Expression* right_expr;

public:

    Expression();

    void set_left_expr(Expression* expression);

    void set_right_expr(Expression* expression);

    void set_expr_element(ExpressionHandler* expr_element);

    std::string to_string() const;

    const ExpressionHandler* get_expression_handler() const;
};


#endif //PROTOCOL_COMPILER_EXPRESSION_H
