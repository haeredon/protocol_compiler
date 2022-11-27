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
//
//    virtual void visit(While& while_stmt);
//
//    virtual void visit(Switch& switch_stmt);

//    virtual void visit(Field& field_stmt);

    virtual void visit(int x);

    virtual void visit(Field& x);

    virtual void visit(While& x);

    virtual void visit(Switch& x);



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
