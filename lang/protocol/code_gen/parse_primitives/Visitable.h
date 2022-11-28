//
// Created by skod on 11/28/22.
//

#ifndef PROTOCOL_COMPILER_VISITABLE_H
#define PROTOCOL_COMPILER_VISITABLE_H

class ClassVisitor;

class Visitable {

public:

    virtual void visit(ClassVisitor* visitor) const = 0;

};

#endif //PROTOCOL_COMPILER_VISITABLE_H
