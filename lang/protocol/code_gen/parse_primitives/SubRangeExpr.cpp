#include "SubRangeExpr.h"
#include "../ClassVisitor.h"

Expression *SubRangeExpr::get_arg() {
    return arg;
}

void SubRangeExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}

SubRangeExpr::SubRangeExpr(Expression *arg) : arg(arg) {}
