//
// Created by skod on 1/4/22.
//

#ifndef PROTOCOL_COMPILER_BUILDCLASS_H
#define PROTOCOL_COMPILER_BUILDCLASS_H

#include "lang/protocol/code_gen/parse_primitives/Class.h"
#include "ClassVisitor.h"

#include <string>
#include<sstream>

class BuildClass : public ClassVisitor {

private:

    std::stringstream start_ss;
    std::stringstream end_ss;
    std::stringstream private_ss;
    std::stringstream constructor_ss;
    std::stringstream destructor_ss;
    std::stringstream get_data_ss;
    std::stringstream public_ss;

public:

    // TODO: check when copy and when move constructor are used IMPORTANT FOR MAX FUN AND GAIN!
    BuildClass();

    virtual void visit(const Class& x);

    virtual void visit(const Field& x);

    virtual void visit(const While& x);

    virtual void visit(const Switch& x);

    virtual void visit(const PrimitiveExpr& x);


    std::string class_to_string(Class &p_class);

};

#endif //PROTOCOL_COMPILER_BUILDCLASS_H
