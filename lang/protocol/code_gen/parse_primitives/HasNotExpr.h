//
// Created by skod on 12/25/21.
//

#ifndef PROTOCOL_COMPILER_HAS_NOT_H
#define PROTOCOL_COMPILER_HAS_NOT_H


#include "Expression.h"
#include "FunctionExpr.h"
#include "FieldExpr.h"

#include <string>

class ClassVisitor;

class HasNotExpr : public FunctionExpr {

private:

    std::vector<FieldExpr*> args;

public:

    explicit HasNotExpr(std::vector<FieldExpr*>&& args);

    virtual void visit(ClassVisitor* visitor) const;

    std::vector<FieldExpr*>& get_args();
};


#endif //PROTOCOL_COMPILER_HAS_NOT_H
