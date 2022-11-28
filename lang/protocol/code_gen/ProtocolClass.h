//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_PARSECLASS_H
#define PARSER_CODE_GEN_PARSECLASS_H

#include "parse_primitives/Class.h"
#include "parse_primitives/Statement.h"
#include "parse_primitives/Expression.h"
#include "parse_primitives/While.h"
#include "parse_primitives/Switch.h"
#include "parse_primitives/Field.h"
#include "parse_primitives/Expression.h"
#include "ClassVisitor.h"


#include<sstream>

class ProtocolClassInit : public ClassVisitor {

private:

    std::stringstream ss;

public:

    ProtocolClassInit();

    virtual void visit(const Field& x);

    virtual void visit(const While& x);

    virtual void visit(const Switch& x);

    virtual void visit(const DotExpression& x);

    virtual void visit(const FieldExpr& x);

    virtual void visit(const FunctionExpr& x);

    virtual void visit(const OperatorExpr& x);

    virtual void visit(const PrimitiveExpr& x);

    std::string to_string();


};


class ProtocolClass {

private:

    std::stringstream ss;

public:

    // TODO: check when copy and when move constructor are used IMPORTANT FOR MAX FUN AND GAIN!
    ProtocolClass();

    std::string class_to_string(Class &p_class);

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
