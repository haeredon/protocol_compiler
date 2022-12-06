#include "HasNotExpr.h"
#include "../ClassVisitor.h"

HasNotExpr::HasNotExpr(std::vector<FieldExpr *> &&args) : args(std::move(args)) {}

void HasNotExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}

const std::vector<FieldExpr *> &HasNotExpr::get_args() const {
    return args;
}
