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

    std::stringstream inheritance_stream;
    std::stringstream private_var_stream;

    std::stringstream constructor_stream;
    std::stringstream destructor_stream;
    std::stringstream init_method_stream;

    std::stringstream public_method_stream;
    std::stringstream to_data_method_stream;

public:

    ProtocolClass();


    std::string class_to_string(const Class &p_class);

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
