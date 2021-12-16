//
// Created by skod on 12/7/21.
//

#include "FieldGroup.h"

void FieldGroup::set_is_continue(Expression* is_continue) {
    this->is_continue = is_continue;
}

void FieldGroup::add_field(Field field) {
    fields.push_back(field);
}
