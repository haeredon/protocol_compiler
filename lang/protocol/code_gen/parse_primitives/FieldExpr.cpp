//
// Created by skod on 12/25/21.
//

#include "FieldExpr.h"
#include<sstream>


FieldExpr::FieldExpr(const Field &field) : field(field) {
}

std::string FieldExpr::to_string() {
    std::stringstream ss;
    ss << "Util::flip_endian(data[" << field.get_name() << "], " << field.get_length()->to_string() << ");";
    return ss.str();
}


