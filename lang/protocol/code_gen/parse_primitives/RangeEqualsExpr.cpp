#include "RangeEqualsExpr.h"
#include "../ClassVisitor.h"

RangeEqualsExpr::RangeEqualsExpr(Expression *offset, Expression *length, Expression *value) :
    offset(offset), length(length), value(value) {}

void RangeEqualsExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(this);
}

Expression *RangeEqualsExpr::get_offset() {
    return offset;
}

Expression *RangeEqualsExpr::get_length() {
    return length;
}

Expression *RangeEqualsExpr::get_value() {
    return value;
}
