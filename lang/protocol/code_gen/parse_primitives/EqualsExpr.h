//
// Created by skod on 12/25/21.
//

#ifndef PROTOCOL_COMPILER_EQUALS_H
#define PROTOCOL_COMPILER_EQUALS_H


#include "Expression.h"
#include "FunctionExpr.h"

#include <string>

class ClassVisitor;

class EqualsExpr : public FunctionExpr {

private:

    std::vector<Expression*> args;

public:

    explicit EqualsExpr(std::vector<Expression*>&& args);

    virtual void visit(ClassVisitor* visitor) const;

    const std::vector<Expression*>& get_args() const;
};


#endif //PROTOCOL_COMPILER_EQUALS_H
