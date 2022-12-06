//
// Created by skod on 12/25/21.
//

#ifndef PROTOCOL_COMPILER_SUB_RANGE_H
#define PROTOCOL_COMPILER_SUB_RANGE_H

#include "Expression.h"
#include "FunctionExpr.h"

#include <string>

class ClassVisitor;

class SubRangeExpr : public FunctionExpr {

private:

    Expression* arg;

public:

    explicit SubRangeExpr(Expression* arg);

    virtual void visit(ClassVisitor* visitor) const;

    const Expression* get_arg() const;
};


#endif //PROTOCOL_COMPILER_SUB_RANGE_H
