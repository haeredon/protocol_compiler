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

void Class::add_while(While while_obj) {
    whiles.push_back(while_obj);
}

bool Class::has_field(const std::string& field_name) {
    return std::any_of(fields.begin(), fields.end(), [field_name](Field& field){ return field.get_name() == field_name; });
}

Field& Class::get_field(const std::string& field_name) {
    for(Field& field : fields) {
        if(field.get_name() == field_name) {
            return field;
        }
    }

    throw std::exception();
}

std::list<Field> &Class::get_fields() {
    return fields;
}

const std::vector<While> &Class::get_while() const {
    return whiles;
}

const std::string &Class::get_name() const {
    return name;
}

const NextProtocol &Class::get_next_protocol() const {
    return next_protocol;
}

void Class::set_next_protocol(NextProtocol&& nextProtocol) {
    next_protocol = std::move(nextProtocol);
}
