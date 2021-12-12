//
// Created by skod on 12/7/21.
//

#include "Enumeration.h"


void Enumeration::add_val(std::string name, std::size_t val) {
    enum_to_val[name] = val;
}
