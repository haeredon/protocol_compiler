#include "EqualsExpr.h"
#include "../ClassVisitor.h"

void EqualsExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}

const std::vector<Expression *> &EqualsExpr::get_args() const {
    return args;
}

EqualsExpr::EqualsExpr(std::vector<Expression *> &&args) : args(std::move(args)) {}
