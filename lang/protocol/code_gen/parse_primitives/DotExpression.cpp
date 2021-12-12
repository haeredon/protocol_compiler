//
// Created by skod on 12/12/21.
//

#include "DotExpression.h"

void DotExpression::set_top(ExprElement* top) {
    this->top = top;
}

void DotExpression::add_chain_element(const std::string &chain_element) {
    this->chain.push_back(chain_element);
}
