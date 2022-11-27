//
// Created by skod on 12/7/21.
//

#include "Case.h"

Case::Case(Expression* match, Statement* stmt) : match(match), stmt(stmt) {}

const Statement* Case::get_statement() const {
    return stmt;
}

Expression* Case::get_match() const {
    return match;
}