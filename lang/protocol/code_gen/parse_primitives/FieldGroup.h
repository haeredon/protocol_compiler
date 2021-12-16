//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_FIELDGROUP_H
#define PROTOCOL_COMPILER_FIELDGROUP_H

#include "Field.h"
#include "Expression.h"

#include <vector>

class FieldGroup {

    std::vector<Field> fields;

    Expression* is_continue;

public:
    void set_is_continue(Expression* expression);

    void add_field(Field field);
};


#endif //PROTOCOL_COMPILER_FIELDGROUP_H
