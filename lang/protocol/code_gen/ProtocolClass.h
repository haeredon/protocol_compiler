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

    void prepare_fields(Class &p_class);

    static std::string field_to_string_handler(const Field& field);

public:

    // TODO: check when copy and when move constructor are used IMPORTANT FOR MAX FUN AND GAIN!
    ProtocolClass();

    std::string class_to_string(Class &p_class);

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
