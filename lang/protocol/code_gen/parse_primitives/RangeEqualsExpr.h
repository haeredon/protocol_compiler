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

    const Expression* get_offset() const ;

    const Expression* get_length() const ;

    const Expression* get_value() const ;
};


#endif //PROTOCOL_COMPILER_RANGE_EQUALS_H
