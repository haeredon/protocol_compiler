//
// Created by skod on 12/7/21.
//

#include "Expression.h"

void Expression::set_left_expr(Expression* expression) {
    this->left_expr = expression;
}

void Expression::set_right_expr(Expression* expression) {
    this->right_expr = expression;
}

void Expression::set_expr_element(ExprElement expr_element) {
    this->expr_element = expr_element;
}

std::string Expression::to_string(std::function<std::string(ExprElement)> handler) {
    return left_expr->to_string(handler) + expr_element.to_string(handler) + right_expr->to_string(handler);
}
