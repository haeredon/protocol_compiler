//
// Created by skod on 11/22/22.
//

#ifndef PROTOCOL_COMPILER_STATEMENT_H
#define PROTOCOL_COMPILER_STATEMENT_H

#include "Visitable.h"

#include <string>

class ClassVisitor;

class Statement : public Visitable {


public:

    virtual std::string to_string() { return "NONE"; };

    virtual void visit(ClassVisitor* visitor) const = 0;

};

#endif //PROTOCOL_COMPILER_STATEMENT_H
