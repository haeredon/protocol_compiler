//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_CLASS_H
#define PARSER_CODE_GEN_CLASS_H

#include "Field.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cmath>

class BaseClass {

protected:

    std::vector<Field> fields;

    std::string name;

    static inline const std::string TAB = "\t";

    virtual std::string get_inheritance() = 0;

    virtual std::string get_privates() = 0;

    virtual std::string get_constructor() = 0;

    virtual std::string get_destructor() = 0;

    virtual std::string get_getters() = 0;

    virtual std::string get_setters() = 0;

public:

    BaseClass(std::string name) : name(name) {}

    void add_name(std::string& name) {
        this->name = name;
    };

    std::string& get_name() {
        return name;
    }

    virtual std::string to_string() = 0;

    void add_field(Field&& field) {
        fields.push_back(field);
    }


};


#endif //PARSER_CODE_GEN_CLASS_H
