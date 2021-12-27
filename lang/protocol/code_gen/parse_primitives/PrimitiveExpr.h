//
// Created by skod on 12/11/21.
//

#ifndef PROTOCOL_COMPILER_PRIMITIVEEXPR_H
#define PROTOCOL_COMPILER_PRIMITIVEEXPR_H

#include "ExpressionHandler.h"

#include <string>

class PrimitiveExpr : public ExpressionHandler {

    std::string value;


public:

    PrimitiveExpr(const std::string& value);

    std::string to_string();

};


#endif //PROTOCOL_COMPILER_PRIMITIVEEXPR_H
