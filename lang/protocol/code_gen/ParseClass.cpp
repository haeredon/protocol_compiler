//
// Created by skod on 11/05/2021.
//

#include "ParseClass.h"

#include<sstream>

ParseClass::ParseClass() : BaseClass("DEFAULT") {

}

std::string ParseClass::to_string() {
    std::stringstream ss;

    ss << "class " << get_name() << " " << get_inheritance() << " { " << std::endl << std::endl;

    ss << "private: " << std::endl << std::endl;

    ss << get_privates() << std::endl << std::endl;

    ss << "public:" << std::endl << std::endl;

    ss << get_constructor() << std::endl << std::endl;

    ss << get_getters() << std::endl << std::endl;

    ss << "}";

    return ss.str();
}




