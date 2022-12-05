//
// Created by skod on 11/24/22.
//

#ifndef PROTOCOL_COMPILER_CLASSVISITOR_H
#define PROTOCOL_COMPILER_CLASSVISITOR_H

#include "parse_primitives/Field.h"
#include "parse_primitives/While.h"
#include "parse_primitives/Switch.h"
#include "parse_primitives/Expression.h"
#include "parse_primitives/DotExpression.h"
#include "parse_primitives/FieldExpr.h"
#include "parse_primitives/FunctionExpr.h"
#include "parse_primitives/OperatorExpr.h"
#include "parse_primitives/PrimitiveExpr.h"
#include "parse_primitives/RangeEqualsExpr.h"
#include "parse_primitives/EqualsExpr.h"
#include "parse_primitives/HasNotExpr.h"
#include "parse_primitives/SubRangeExpr.h"
#include "parse_primitives/Class.h"

class ClassVisitor {

public:

    virtual void visit(const Class& x) = 0;

    virtual void visit(const Field& x) = 0;

    virtual void visit(const While& x) = 0;

    virtual void visit(const Switch& x) = 0;

    virtual void visit(const DotExpression& x) {
        throw "Not implemented";
    };

    virtual void visit(const FieldExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const FunctionExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const OperatorExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const PrimitiveExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const RangeEqualsExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const EqualsExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const SubRangeExpr& x) {
        throw "Not implemented";
    };

    virtual void visit(const HasNotExpr& x) {
        throw "Not implemented";
    };
};

#endif //PROTOCOL_COMPILER_CLASSVISITOR_H
