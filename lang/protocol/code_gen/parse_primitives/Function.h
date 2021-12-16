//
// Created by skod on 12/12/21.
//

#ifndef PROTOCOL_COMPILER_FUNCTION_H
#define PROTOCOL_COMPILER_FUNCTION_H

#include "Expression.h"

#include <string>
#include <vector>

class Function : public ExprElement {

    std::string name;

    std::vector<Expression*> args;

public:
    void add_arg(Expression* expression);
};


#endif //PROTOCOL_COMPILER_FUNCTION_H
