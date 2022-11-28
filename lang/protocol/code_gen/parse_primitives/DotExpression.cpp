//
// Created by skod on 12/12/21.
//

#include "DotExpression.h"
#include "../ClassVisitor.h"

//void DotExpression::set_top(ExprElement* top) {
//    this->top = top;
//}

void DotExpression::add_chain_element(const std::string &chain_element) {
    this->chain.push_back(chain_element);
}

std::string DotExpression::to_string() {
    return std::string();
}

void DotExpression::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}
