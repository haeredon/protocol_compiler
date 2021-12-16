//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_EXPRESSION_H
#define PROTOCOL_COMPILER_EXPRESSION_H

#include "ExprElement.h"

#include <string>
#include <functional>

class Expression {


    ExprElement expr_element;
    Expression* left_expr;
    Expression* right_expr;

public:
    void set_left_expr(Expression* expression);

    void set_right_expr(Expression* expression);

    void set_expr_element(ExprElement expr_element);

    std::string to_string(std::function<std::string(ExprElement)> handler);
};


#endif //PROTOCOL_COMPILER_EXPRESSION_H
