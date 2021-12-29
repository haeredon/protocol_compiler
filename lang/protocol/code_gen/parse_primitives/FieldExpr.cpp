//
// Created by skod on 12/25/21.
//

#include "FieldExpr.h"
#include<sstream>


FieldExpr::FieldExpr(const Field &field) : field(field) {
}

std::string FieldExpr::to_string() {
    std::stringstream ss;
    ss << "Util::flip_endian(data[" << field.get_name() << ".offset], " << field.get_name() << ".length" << ")";
    return ss.str();
}

const Field &FieldExpr::get_field() const {
    return field;
}


