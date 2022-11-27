//
// Created by skod on 11/22/22.
//

#ifndef PROTOCOL_COMPILER_STATEMENT_H
#define PROTOCOL_COMPILER_STATEMENT_H

#include <string>

class ClassVisitor;

class Statement {


public:

    virtual std::string to_string() { return "NONE"; };

    virtual void visit(ClassVisitor* visitor) = 0;

};

#endif //PROTOCOL_COMPILER_STATEMENT_H
