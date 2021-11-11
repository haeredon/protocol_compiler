//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_CLASS_H
#define PARSER_CODE_GEN_CLASS_H

#include "Field.h"
#include "Node.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cmath>

class BaseClass {

protected:

    std::vector<Field> fields;

    std::vector<std::string> next_protocol_args;

    std::string name;

    static inline const std::string TAB = "\t";

    virtual std::string get_inheritance() = 0;

    virtual std::string get_privates() = 0;

    virtual std::string get_constructor() = 0;

    virtual std::string get_destructor() = 0;

    virtual std::string get_getters() = 0;

    virtual std::string get_setters() = 0;

    virtual std::string parse_length_expr(ProtocolParser::Node* ast) {
        std::regex num_regex ("^([0-9]*$).*");
        std::smatch match;

        std::string value = ast->get_value();

        std::vector<ProtocolParser::Node*>& children = ast->get_children();
        bool is_num = std::regex_search (value, match, num_regex);

        if(value == "+" || value == "-" || value == "/" || value == "*") {
            return parse_length_expr(children.front()) + value + parse_length_expr(children[1]);
        } else if(!is_num) {
            return "Util::flip_endian(Util::to_numeric<uint_arc>(" + value + ".data(), " + value + ".size()), " + value + ".size()" + ")";;
        } else {
            return value;
        }
    };

    //    std::string get_expression(ProtocolParser::Node* ast) {

    //    }
    //
    //    std::string get_length_dependency(ProtocolParser::Node* ast) {
    //        std::string value = ast->get_value();
    //
    //        std::vector<ProtocolParser::Node*>& children = ast->get_children();
    //
    //        if(value == "+" || value == "-" || value == "/" || value == "*") {
    //            return get_expression(children.front()) + value + get_expression(children[1]);
    //        } else {
    //            return value;
    //        }
    //    }


    Field& get_field_by_name(const std::string& name) {
        for(auto it = fields.begin() ; it != fields.end() ; ++it) {
            if(it->get_name() == name) {
                return *it;
            }
        }
        throw "no field with given name";
    }

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

    void set_next_protocol(std::vector<std::string> args) {
        next_protocol_args = args;
    }


};


#endif //PARSER_CODE_GEN_CLASS_H
