//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_WHILE_H
#define PROTOCOL_COMPILER_WHILE_H

#include "Field.h"
#include "Expression.h"
#include "Statement.h"

#include <vector>
#include <list>

class While : public Statement {

    std::list<Statement> statements;

    Expression* continue_conditional;

public:

    While(Expression* continue_conditional, std::list<Statement>&& stmts);

    void set_continue_conditional(Expression* expression);

    void add_statement(Statement statement);

    const std::list<Statement> &get_statement() const;

    Expression *get_continue_conditional() const;
};


#endif //PROTOCOL_COMPILER_WHILE_H
