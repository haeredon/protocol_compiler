//
// Created by skod on 12/7/21.
//

#include "Field.h"

void Field::set_name(std::string name) {
    this->name = name;
}

void Field::set_length(Expression length) {
    this->length = length;
}

void Field::set_is_included(Expression is_included) {
    this->is_included = is_included;
}

void Field::set_bitmap(Bitmap bitmap) {
    this->bitmap = bitmap;
}

void Field::set_enumeration(Enumeration enumeration) {
    this->enumeration = enumeration;
}

const std::string& Field::get_name() {
    return name;
}
