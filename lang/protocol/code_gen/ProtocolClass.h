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

    std::string class_to_string(Class &p_class);

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
