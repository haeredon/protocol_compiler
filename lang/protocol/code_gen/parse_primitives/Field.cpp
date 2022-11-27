//
// Created by skod on 12/7/21.
//

#include "Field.h"
#include "../ClassVisitor.h"

#include <iostream>

void Field::set_name(std::string name) {
    this->name = name;
}

void Field::set_length(Expression* length) {
    this->length = length;
}

void Field::set_is_included(Expression* is_included) {
    this->is_included = is_included;
}

void Field::set_bitmap(Bitmap bitmap) {
    this->bitmap = bitmap;
}

void Field::set_enumeration(Enumeration enumeration) {
    this->enumeration = enumeration;
}

const std::string& Field::get_name() const {
    return name;
}

std::string Field::to_string() {
    std::cout << to_string_handler.target<std::function<std::string(const Field&)>>();
    return to_string_handler(*this);
}

const Expression* Field::get_length() const {
    return length;
}

Expression *Field::get_is_included() const {
    return is_included;
}

Field::Field() : is_included(nullptr) {}

const Enumeration &Field::get_enumeration() const {
    return enumeration;
}

const Bitmap &Field::get_bitmap() const {
    return bitmap;
}

void Field::visit(ClassVisitor* visitor) {
    visitor->visit(*this);
}
