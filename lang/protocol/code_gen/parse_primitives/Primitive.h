//
// Created by skod on 12/11/21.
//

#ifndef PROTOCOL_COMPILER_PRIMITIVE_H
#define PROTOCOL_COMPILER_PRIMITIVE_H

#include "ExprElement.h"

#include <string>

class Primitive : public ExprElement {


public:

    Primitive(const std::string& value);
};


#endif //PROTOCOL_COMPILER_PRIMITIVE_H
