//
// Created by skod on 12/14/21.
//

#ifndef PROTOCOL_COMPILER_OPERATOR_H
#define PROTOCOL_COMPILER_OPERATOR_H

#include "ExprElement.h"

#include <string>

class Operator : public ExprElement {

public:
    Operator(const std::string& value);
};


#endif //PROTOCOL_COMPILER_OPERATOR_H
