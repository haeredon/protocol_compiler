//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_FIELD_H
#define PROTOCOL_COMPILER_FIELD_H

#include "Expression.h"
#include "Bitmap.h"
#include "Enumeration.h"
#include "ExprElement.h"

#include <string>

class Field : public ExprElement {

    std::string name;

    Expression length;

    Expression is_included;

    Enumeration enumeration;

    Bitmap bitmap;

public:
    void set_name(std::string name);

    void set_length(Expression expression);

    void set_is_included(Expression expression);

    void set_bitmap(Bitmap bitmap);

    void set_enumeration(Enumeration enumeration);

    void test() {};

    const std::string& get_name();
};


#endif //PROTOCOL_COMPILER_FIELD_H
