//
// Created by skod on 12/12/21.
//

#ifndef PROTOCOL_COMPILER_DOTEXPRESSION_H
#define PROTOCOL_COMPILER_DOTEXPRESSION_H

#include "ExprElement.h"

#include <string>
#include <vector>

class DotExpression : public ExprElement  {

    ExprElement* top;

    std::vector<std::string> chain;
public:
    void set_top(ExprElement* top);

    void add_chain_element(const std::string &chain_element);
};


#endif //PROTOCOL_COMPILER_DOTEXPRESSION_H
