//
// Created by skod on 11/23/22.
//

#ifndef PROTOCOL_COMPILER_SWITCH_H
#define PROTOCOL_COMPILER_SWITCH_H

#include "Statement.h"
#include "Case.h"
#include "Expression.h"

#include <list>

class Switch : public Statement {

private:

    Expression* compare_value;

    std::list<Case> cases;

public:

    Switch(Expression* compare_value, std::list<Case>&& cases);

    const Expression* get_compare_value() const;

    const std::list<Case>& get_cases() const;

};


#endif //PROTOCOL_COMPILER_SWITCH_H
