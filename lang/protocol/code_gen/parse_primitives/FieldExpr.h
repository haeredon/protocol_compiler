//
// Created by skod on 12/25/21.
//

#ifndef PROTOCOL_COMPILER_FIELDEXPR_H
#define PROTOCOL_COMPILER_FIELDEXPR_H


#include "Expression.h"
#include "Field.h"

#include <string>

class FieldExpr : public Expression {

private:

    const Field& field;

public:

    FieldExpr(const Field &field);

    std::string to_string() const;

    const Field& get_field() const;

};


#endif //PROTOCOL_COMPILER_FIELDEXPR_H
