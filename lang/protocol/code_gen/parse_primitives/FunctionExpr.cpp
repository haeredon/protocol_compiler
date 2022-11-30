//
// Created by skod on 12/12/21.
//

#include "FunctionExpr.h"
#include "FieldExpr.h"
#include "../ClassVisitor.h"

#include<sstream>

void FunctionExpr::add_arg(Expression* expression) {
    args.push_back(expression);
}

const std::vector<Expression*>& FunctionExpr::get_args() const {
    return args;
}

const std::string FunctionExpr::get_name() const {
    return name;
}

void FunctionExpr::set_name(const std::string &name) {
    this->name = name;
}

void FunctionExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}
