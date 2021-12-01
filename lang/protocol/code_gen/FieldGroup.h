//
// Created by skod on 12/1/21.
//

#ifndef PROTOCOL_COMPILER_FIELDGROUP_H
#define PROTOCOL_COMPILER_FIELDGROUP_H


#include "Conditional.h"

class FieldGroup {

private:

    Conditional conditional;
    std::vector<Field> fields;

public:

    FieldGroup(const Conditional &conditional, const std::vector <Field> &fields) : conditional(conditional),
                                                                                    fields(fields) {}

    FieldGroup() {}

    const Conditional &getConditional() const {
        return conditional;
    }

    const std::vector<Field> &getFields() const {
        return fields;
    }

};


#endif //PROTOCOL_COMPILER_FIELDGROUP_H
