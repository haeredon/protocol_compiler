//
// Created by skod on 12/7/21.
//

#include "Enumeration.h"


void Enumeration::add_val(std::string name, std::size_t val) {
    enum_to_val[name] = val;
}

const std::unordered_map<std::string, std::size_t> &Enumeration::get_enum_to_Val() const {
    return enum_to_val;
}
