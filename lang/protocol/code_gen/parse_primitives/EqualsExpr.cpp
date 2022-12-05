#include "EqualsExpr.h"
#include "../ClassVisitor.h"

void EqualsExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(this);
}

std::vector<Expression *> &EqualsExpr::get_args() {
    return args;
}

EqualsExpr::EqualsExpr(std::vector<Expression *> &&args) : args(std::move(args)) {}
