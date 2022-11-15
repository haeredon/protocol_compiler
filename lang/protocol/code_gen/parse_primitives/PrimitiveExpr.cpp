//
// Created by skod on 12/11/21.
//

#include "PrimitiveExpr.h"

PrimitiveExpr::PrimitiveExpr(const std::string& value) : Expression(), value(value) {}

std::string PrimitiveExpr::to_string() const {
    return value;
}


std::endian PrimitiveExpr::get_endianness() {
    return std::endian::little;
}