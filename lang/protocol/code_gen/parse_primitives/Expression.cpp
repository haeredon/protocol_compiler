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

void Expression::set_expr_element(ExpressionHandler* expr_element) {
    this->expr_element = expr_element;
}

std::string Expression::to_string() const {
    return (left_expr == nullptr ? "" : left_expr->to_string()) +
            expr_element->to_string() +
            (right_expr == nullptr ? "" : right_expr->to_string());
}

Expression::Expression() : expr_element(nullptr), left_expr(nullptr), right_expr(nullptr) {

}

const ExpressionHandler *Expression::get_expression_handler() const {
    return expr_element;
}
