#include "RangeEqualsExpr.h"
#include "../ClassVisitor.h"

RangeEqualsExpr::RangeEqualsExpr(Expression *offset, Expression *length, Expression *value) :
    offset(offset), length(length), value(value) {}

void RangeEqualsExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}

const Expression *RangeEqualsExpr::get_offset() const  {
    return offset;
}

const Expression *RangeEqualsExpr::get_length() const  {
    return length;
}

const Expression *RangeEqualsExpr::get_value() const {
    return value;
}
