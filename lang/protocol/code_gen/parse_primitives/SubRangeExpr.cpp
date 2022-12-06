#include "SubRangeExpr.h"
#include "../ClassVisitor.h"

const Expression *SubRangeExpr::get_arg() const {
    return arg;
}

void SubRangeExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}

SubRangeExpr::SubRangeExpr(Expression *arg) : arg(arg) {}
