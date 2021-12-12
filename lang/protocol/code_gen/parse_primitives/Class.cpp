//
// Created by skod on 12/7/21.
//

#include "Class.h"

#include <algorithm>

void Class::set_name(std::string name) {
    this->name = name;
}

void Class::add_field(Field field) {
    fields.push_back(field);
}

void Class::add_field_group(FieldGroup group) {
    field_groups.push_back(group);
}

void Class::add_property(Property property) {
    properties.push_back(property);
}

bool Class::has_field(const std::string& field_name) {
//    return std::any_of(fields.cbegin(), fields.cend(), [field_name](Field& field){ return field.get_name() == field_name; });
    return true;
}

Field& Class::get_field(const std::string& field_name) {
    for(Field& field : fields) {
        if(field.get_name() == field_name) {
            return  field;
        }
    }

    throw std::exception();
}
