//
// Created by skod on 12/11/21.
//

#include "PrimitiveExpr.h"
#include "../ClassVisitor.h"

PrimitiveExpr::PrimitiveExpr(const std::string& value) : Expression(), value(value) {}

std::string PrimitiveExpr::to_string() const {
    return value;
}

void PrimitiveExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}

