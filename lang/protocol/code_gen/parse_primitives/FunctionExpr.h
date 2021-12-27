//
// Created by skod on 12/12/21.
//

#ifndef PROTOCOL_COMPILER_FUNCTIONEXPR_H
#define PROTOCOL_COMPILER_FUNCTIONEXPR_H

#include "Expression.h"
#include "ExpressionHandler.h"

#include <string>
#include <vector>

class FunctionExpr : public ExpressionHandler {

    std::string name;

    std::vector<Expression*> args;

public:
    void add_arg(Expression* expression);

    void set_name(const std::string &name);

    std::string to_string();
};


#endif //PROTOCOL_COMPILER_FUNCTIONEXPR_H
