//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_FIELDGROUP_H
#define PROTOCOL_COMPILER_FIELDGROUP_H

#include "Field.h"
#include "Expression.h"

#include <vector>
#include <list>

class FieldGroup {

    std::list<Field> fields;

    Expression* is_continue;

public:
    void set_is_continue(Expression* expression);

    void add_field(Field field);

    const std::list<Field> &get_fields() const;

    Expression *get_is_continue() const;
};


#endif //PROTOCOL_COMPILER_FIELDGROUP_H
