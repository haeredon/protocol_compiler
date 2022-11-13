//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_PARSECLASS_H
#define PARSER_CODE_GEN_PARSECLASS_H

#include "parse_primitives/Class.h"
#include<sstream>

class ProtocolClass {

private:

    std::stringstream ss;

public:

    // TODO: check when copy and when move constructor are used IMPORTANT FOR MAX FUN AND GAIN!
    ProtocolClass();

    std::string length_to_type(short length) {
        switch (length) {
            case 1:
                return "uint8_t";
            case 2:
                return "uint16_t";
            case 4:
                return "uint32_t";
            case 8:
                return "uint64_t";
            default:
                throw "length: " + std::to_string(length) + " does not convert to a type";
        }
    }

    std::string class_to_string(Class &p_class);

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
