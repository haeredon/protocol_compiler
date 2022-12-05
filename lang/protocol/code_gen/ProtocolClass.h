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




class ProtocolClass : public ClassVisitor {

private:

    class ProtocolClassInit : public ClassVisitor {

    private:

        std::stringstream ss;
        bool expect_little_end = true;

    public:

        ProtocolClassInit();

        virtual void visit(const Class& x);

        virtual void visit(const Field& x);

        virtual void visit(const While& x);

        virtual void visit(const Switch& x);

        virtual void visit(const DotExpression& x);

        virtual void visit(const FieldExpr& x);

        virtual void visit(const RangeEqualsExpr &x);

        virtual void visit(const EqualsExpr &x);

        virtual void visit(const HasNotExpr &x);

        virtual void visit(const SubRangeExpr &x);

        virtual void visit(const OperatorExpr& x);

        virtual void visit(const PrimitiveExpr& x);

        std::string to_string();


    };


    std::stringstream ss_start;
    std::stringstream ss_end;
    std::stringstream private_ss;
    std::stringstream public_ss;
    std::stringstream* target_ss;

    ProtocolClassInit initMethod;

public:

    // TODO: check when copy and when move constructor are used IMPORTANT FOR MAX FUN AND GAIN!
    ProtocolClass();

    virtual void visit(const Class& x);

    virtual void visit(const Field& x);

    virtual void visit(const While& x);

    virtual void visit(const Switch& x);

    virtual void visit(const PrimitiveExpr& x);


    std::string class_to_string(Class &p_class);

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
