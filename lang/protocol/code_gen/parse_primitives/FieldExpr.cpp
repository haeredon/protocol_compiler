//
// Created by skod on 12/25/21.
//

#include "FieldExpr.h"
#include<sstream>


FieldExpr::FieldExpr(const Field &field) : Expression(), field(field) {
}

std::string FieldExpr::to_string() const {
    std::stringstream ss;
    ss << "Util::flip_endian_to_num<uint64_t>(data +" << field.get_name() << ".offset, " << field.get_name() << ".length" << ")";
    return ss.str();
}

const Field &FieldExpr::get_field() const {
    return field;
}


