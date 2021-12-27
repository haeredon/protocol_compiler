//
// Created by skod on 12/24/21.
//

#ifndef PROTOCOL_COMPILER_EXPRESSIONHANDLER_H
#define PROTOCOL_COMPILER_EXPRESSIONHANDLER_H

#include <string>

class ExpressionHandler {

public:
    virtual std::string to_string() = 0;

};


#endif //PROTOCOL_COMPILER_EXPRESSIONHANDLER_H
