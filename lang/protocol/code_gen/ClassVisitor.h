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
#include "parse_primitives/Class.h"

class ClassVisitor {

public:

//    virtual void visit(While& while_stmt) = 0;
//
//    virtual void visit(Switch& switch_stmt) = 0;

    virtual void visit(const Class& x) = 0;

    virtual void visit(const Field& x) = 0;

    virtual void visit(const While& x) = 0;

    virtual void visit(const Switch& x) = 0;

    virtual void visit(const DotExpression& x) {
        std::cout << "DotExpression" << std::endl;
    };

    virtual void visit(const FieldExpr& x) {
        std::cout << "FieldExpr" << std::endl;
    };

    virtual void visit(const FunctionExpr& x) {
        std::cout << "FunctionExpr" << std::endl;
    };

    virtual void visit(const OperatorExpr& x) {
        std::cout << "OperatorExpr" << std::endl;
    };

    virtual void visit(const PrimitiveExpr& x) {
        std::cout << "PrimitiveExpr" << std::endl;
    };

};

#endif //PROTOCOL_COMPILER_CLASSVISITOR_H
