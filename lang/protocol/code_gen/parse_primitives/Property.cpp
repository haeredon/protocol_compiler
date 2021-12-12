//
// Created by skod on 12/10/21.
//

#include "Property.h"

void Property::set_name(std::string name) {
    this->name = name;
}

void Property::add_arg(std::string& arg) {
    this->args.push_back(arg);
}
