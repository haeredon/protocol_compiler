//
// Created by skod on 12/7/21.
//

#include "While.h"

void While::set_continue_conditional(Expression* is_continue) {
    this->is_continue = is_continue;
}

void While::add_statement(Statement statement) {
    statements.push_back(statement);
}

const std::list<Statement> &While::get_statement() const {
    return statements;
}

Expression *While::get_continue_conditional() const {
    return continue_conditional;
}

While::While(Expression *continue_conditional, std::list<Statement> &&stmts) :
continue_conditional(continue_conditional), statements(std::move(stmts)) {}
