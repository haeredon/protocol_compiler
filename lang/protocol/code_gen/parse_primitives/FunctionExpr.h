//
// Created by skod on 12/12/21.
//

#ifndef PROTOCOL_COMPILER_FUNCTIONEXPR_H
#define PROTOCOL_COMPILER_FUNCTIONEXPR_H

#include "Expression.h"


#include <string>
#include <vector>

class ClassVisitor;

class FunctionExpr : public Expression {

    std::string name;

public:

    void set_name(const std::string &name);

    const std::string get_name() const;

};


#endif //PROTOCOL_COMPILER_FUNCTIONEXPR_H
