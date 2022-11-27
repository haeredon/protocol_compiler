//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_CASE_H
#define PROTOCOL_COMPILER_CASE_H

#include "Field.h"
#include "Expression.h"
#include "Statement.h"

#include <vector>
#include <list>

class Case {

    Expression* match;

    Statement* stmt;

public:

    Case(Expression* match, Statement* stmt);

    const Statement* get_statement() const;

    Expression *get_match() const;
};


#endif //PROTOCOL_COMPILER_CASE_H
