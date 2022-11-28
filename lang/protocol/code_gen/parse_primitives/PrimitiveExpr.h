//
// Created by skod on 12/11/21.
//

#ifndef PROTOCOL_COMPILER_PRIMITIVEEXPR_H
#define PROTOCOL_COMPILER_PRIMITIVEEXPR_H

#include "Expression.h"

#include <string>

class ClassVisitor;

class PrimitiveExpr : public Expression {

    std::string value;


public:

    PrimitiveExpr(const std::string& value);

    std::string to_string() const;

    virtual void visit(ClassVisitor* visitor) const;
};


#endif //PROTOCOL_COMPILER_PRIMITIVEEXPR_H
