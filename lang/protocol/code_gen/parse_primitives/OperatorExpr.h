//
// Created by skod on 12/14/21.
//

#ifndef PROTOCOL_COMPILER_OPERATOREXPR_H
#define PROTOCOL_COMPILER_OPERATOREXPR_H

#include "ExpressionHandler.h"
#include "lang/protocol/Tokens.h"

#include <string>
#include <unordered_map>


class OperatorExpr : public ExpressionHandler {

    std::string value;

    static const std::unordered_map<std::string, std::string> symbol_to_op;

public:

    OperatorExpr(const std::string& value);

    std::string to_string();
};




#endif //PROTOCOL_COMPILER_OPERATOREXPR_H
