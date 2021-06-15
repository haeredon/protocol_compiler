//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_PARSECLASS_H
#define PARSER_CODE_GEN_PARSECLASS_H

#include "BaseClass.h"

#include<sstream>

class ParseClass : public BaseClass {

public:

    ParseClass() : BaseClass("DEFAULT") {

    }

    std::string to_string() {
        std::stringstream ss;

        ss << "class " << this->get_name() << " " << this->get_inheritance() << " { " << std::endl << std::endl;

        ss << "private: " << std::endl << std::endl;

        ss << this->get_privates() << std::endl << std::endl;

        ss << "public:" << std::endl << std::endl;

        ss << this->get_constructor() << std::endl << std::endl;

        ss << this->get_getters() << std::endl << std::endl;

        ss << "}";

        return ss.str();
    }

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
