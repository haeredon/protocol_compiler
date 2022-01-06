//
// Created by skod on 1/4/22.
//

#ifndef PROTOCOL_COMPILER_BUILDCLASS_H
#define PROTOCOL_COMPILER_BUILDCLASS_H

#include "lang/protocol/code_gen/parse_primitives/Class.h"

#include <string>
#include<sstream>

class BuildClass {

private:

    std::stringstream ss;

public:

    // TODO: check when copy and when move constructor are used IMPORTANT FOR MAX FUN AND GAIN!
    BuildClass();

    std::string class_to_string(Class &p_class);

};

#endif //PROTOCOL_COMPILER_BUILDCLASS_H
