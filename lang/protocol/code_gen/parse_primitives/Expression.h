//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_EXPRESSION_H
#define PROTOCOL_COMPILER_EXPRESSION_H

#include "Visitable.h"

#include <string>
#include <functional>
#include <bit>

class Expression : public Visitable {


public:

    Expression();

    virtual std::string to_string() const = 0;


};




#endif //PROTOCOL_COMPILER_EXPRESSION_H
