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

    std::vector<Expression*> args;

public:
    void add_arg(Expression* expression);

    void set_name(const std::string &name);

    const std::string get_name() const;

    const std::vector<Expression*>& get_args() const;

    std::string to_string() const;

    virtual void visit(ClassVisitor* visitor) const;

};


#endif //PROTOCOL_COMPILER_FUNCTIONEXPR_H
