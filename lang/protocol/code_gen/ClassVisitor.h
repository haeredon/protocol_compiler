//
// Created by skod on 11/24/22.
//

#ifndef PROTOCOL_COMPILER_CLASSVISITOR_H
#define PROTOCOL_COMPILER_CLASSVISITOR_H

#include "parse_primitives/Field.h"
#include "parse_primitives/While.h"
#include "parse_primitives/Switch.h"


class ClassVisitor {

public:

//    virtual void visit(While& while_stmt) = 0;
//
//    virtual void visit(Switch& switch_stmt) = 0;


    virtual void visit(Field& x) = 0;

    virtual void visit(While& x) = 0;

    virtual void visit(Switch& x) = 0;

};

#endif //PROTOCOL_COMPILER_CLASSVISITOR_H
