//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_FIELD_H
#define PARSER_FIELD_H

#include "Node.h"

#include <string>
#include <unordered_map>
#include <cstdint>


class Field {

protected:

    std::string name;

    std::string conditional_name;
    std::vector<std::string> conditional_args;

    ProtocolParser::Node* length_exp;
    std::string length_dependency;

    std::unordered_map<std::string, std::size_t> enumeration;
    std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> bitmap;

    struct inner_t {
        bool is_inner;
        std::size_t priority;

        inner_t(bool is_inner, std::size_t priority) : is_inner(is_inner), priority(priority) {}
        inner_t() : is_inner(false), priority(SIZE_MAX) {}
    } inner;


public:

    Field(std::string name, ProtocolParser::Node* length_exp) : name(name), length_exp(length_exp) {

    }

    Field(std::string name, ProtocolParser::Node* length_exp, std::unordered_map<std::string, std::size_t> enumeration,
          std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> bitmap) : name(name), length_exp(length_exp),
                                                                                          enumeration(enumeration),
                                                                                          bitmap(bitmap) {

    }

    std::string &get_name() {
        return name;
    }

    ProtocolParser::Node* get_length_exp() {
        return length_exp;
    }

    std::string &get_length_dependency() {
        return length_dependency;
    }

    std::unordered_map<std::string, std::size_t> &get_enumeration() {
        return enumeration;
    }

    std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> &get_bitmap() {
        return bitmap;
    }

    std::string& get_conditional_name() {
        return conditional_name;
    }

    std::vector<std::string>& get_conditional_args() {
        return conditional_args;
    }

    void set_conditional(std::string name, std::vector<std::string> args) {
        conditional_name = name;
        conditional_args = args;
    }

    inner_t& get_inner() {
        return inner;
    }

    bool is_conditional() {
        return conditional_name.length() != 0;
    }


};


#endif //PARSER_FIELD_H
