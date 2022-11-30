//
// Created by skod on 12/25/21.
//

#include "FieldExpr.h"
#include "../ClassVisitor.h"

#include<sstream>


FieldExpr::FieldExpr(const Field* field) : Expression(), field(field) {
}


const Field* FieldExpr::get_field() const {
    return field;
}

void FieldExpr::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}




