//
// Created by skod on 12/12/21.
//

#include "FunctionExpr.h"
#include "FieldExpr.h"
#include "../ClassVisitor.h"

#include<sstream>


const std::string FunctionExpr::get_name() const {
    return name;
}

void FunctionExpr::set_name(const std::string &name) {
    this->name = name;
}

