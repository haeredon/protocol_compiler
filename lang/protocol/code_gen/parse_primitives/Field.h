//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_FIELD_H
#define PROTOCOL_COMPILER_FIELD_H

#include "Expression.h"
#include "Bitmap.h"
#include "Enumeration.h"

#include <string>
#include <iostream>
#include <memory>

class Field {

    std::string name;

    Expression* length;

    Expression* is_included;

    Enumeration enumeration;

    Bitmap bitmap;

    std::function<std::string(const Field&)> to_string_handler;

public:
    Field();

    void set_name(std::string name);

    void set_length(Expression* expression);

    void set_is_included(Expression* expression);

    void set_bitmap(Bitmap bitmap);

    void set_enumeration(Enumeration enumeration);

    const Enumeration &get_enumeration() const;

    const std::string& get_name() const;

    const Expression* get_length() const;

    Expression *get_is_included() const;

    const Bitmap &get_bitmap() const;

    std::string to_string();

};


#endif //PROTOCOL_COMPILER_FIELD_H
