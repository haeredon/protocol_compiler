//
// Created by skod on 12/25/21.
//

#include "FieldExpr.h"

#include<sstream>


FieldExpr::FieldExpr(const Field &field) : Expression(), field(field) {
}

std::string FieldExpr::to_string() const {
    std::stringstream ss;

    ss << "Util::big_to_little(data + " << field.get_name() << ".offset, " << field.get_name() << ".length" << ")";
    return ss.str();
}

const Field &FieldExpr::get_field() const {
    return field;
}

