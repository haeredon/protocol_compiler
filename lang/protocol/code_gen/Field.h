//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_FIELD_H
#define PARSER_FIELD_H

#include <string>
#include <unordered_map>

class Field {

protected:

    std::string name;

    std::string conditional_name;
    std::vector<std::string> conditional_args;

    std::string second;

    std::unordered_map<std::string, std::size_t> enumeration;
    std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> bitmap;

    bool inner;

public:

    Field(std::string name, std::string second) : name(name), second(second), inner(false) {

    }

    Field(std::string name, std::string second, std::unordered_map<std::string, std::size_t> enumeration,
          std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> bitmap) : name(name), second(second),
                                                                                          enumeration(enumeration),
                                                                                          bitmap(bitmap), inner(false) {

    }

    std::string &get_name() {
        return name;
    }

    std::string &get_second() {
        return second;
    }

    std::unordered_map<std::string, std::size_t> &get_enumeration() {
        return enumeration;
    }

    std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> &get_bitmap() {
        return bitmap;
    }

    void set_conditional(std::string name, std::vector<std::string> args) {
        conditional_name = name;
        conditional_args = args;
    }

    void set_inner(bool inner) {
        this->inner = inner;
    }

    bool is_inner() {
        return inner;
    }

    bool is_conditional() {
        return conditional_name.length() != 0;
    }


};


#endif //PARSER_FIELD_H
