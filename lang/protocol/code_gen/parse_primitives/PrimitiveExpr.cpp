//
// Created by skod on 12/11/21.
//

#include "PrimitiveExpr.h"

PrimitiveExpr::PrimitiveExpr(const std::string& value) : value(value) {}

std::string PrimitiveExpr::to_string() {
    return value;
}
