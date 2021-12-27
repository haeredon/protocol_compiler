//
// Created by skod on 12/25/21.
//

#ifndef PROTOCOL_COMPILER_FIELDEXPR_H
#define PROTOCOL_COMPILER_FIELDEXPR_H


#include "ExpressionHandler.h"
#include "Field.h"

#include <string>

class FieldExpr : public ExpressionHandler {

private:

    const Field& field;

public:

    FieldExpr(const Field &field);

    std::string to_string();

};


#endif //PROTOCOL_COMPILER_FIELDEXPR_H
