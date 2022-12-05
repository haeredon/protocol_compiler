//
// Created by skod on 12/25/21.
//

#ifndef PROTOCOL_COMPILER_RANGE_EQUALS_H
#define PROTOCOL_COMPILER_RANGE_EQUALS_H


#include "Expression.h"
#include "FunctionExpr.h"

#include <string>

class ClassVisitor;

class RangeEqualsExpr : public FunctionExpr {

private:

    Expression* offset;
    Expression* length;
    Expression* value;

public:

    RangeEqualsExpr(Expression* offset, Expression* length, Expression* value);

    virtual void visit(ClassVisitor* visitor) const;

    Expression* get_offset();

    Expression* get_length();

    Expression* get_value();
};


#endif //PROTOCOL_COMPILER_RANGE_EQUALS_H
