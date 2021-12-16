//
// Created by skod on 12/10/21.
//

#ifndef PROTOCOL_COMPILER_EXPRELEMENT_H
#define PROTOCOL_COMPILER_EXPRELEMENT_H


#include <string>
#include <functional>

class ExprElement {

public:
    std::string to_string(std::function<std::string(ExprElement)> handler);
};


#endif //PROTOCOL_COMPILER_EXPRELEMENT_H
