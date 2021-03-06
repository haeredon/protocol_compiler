//
// Created by skod on 12/12/21.
//

#ifndef PROTOCOL_COMPILER_DOTEXPRESSION_H
#define PROTOCOL_COMPILER_DOTEXPRESSION_H

#include "ExpressionHandler.h"

#include <string>
#include <vector>

class DotExpression : public ExpressionHandler  {

//    ExprElement* top;

    std::vector<std::string> chain;
public:
//    void set_top(ExprElement* top);

    void add_chain_element(const std::string &chain_element);

    std::string to_string();
};


#endif //PROTOCOL_COMPILER_DOTEXPRESSION_H
