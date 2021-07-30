//
// Created by root on 26/07/2021.
//

#ifndef PROTOCOL_COMPILER_BUILDBASECLASS_H
#define PROTOCOL_COMPILER_BUILDBASECLASS_H

#include "BaseClass.h"

class BuildBaseClass : public BaseClass {

protected:

    std::string to_build_name;

    std::string get_inheritance() {
        return "";
    }

    std::string get_privates() {
        std::stringstream ss;

        std::smatch match;
        std::regex num_regex ("^([0-9]*$).*");

        typename std::vector<Field>::iterator it;

        for(it = fields.begin() ; it != fields.end() ; ++it) {
            Field& field = *it;

            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "uint8_t* "<< field.get_name() << ";" << std::endl;

            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "std::size_t "<< field.get_name() << "_length";

            bool depends_on_var = !std::regex_search (field.get_second(), match, num_regex);

            if(!depends_on_var) {
                ss << " = " << field.get_second();
            }

            ss << ";" << std::endl << std::endl;
        }

        return ss.str();
    }

    std::string get_constructor() {
        return "";

    }

    std::string get_getters() {
        std::stringstream ss;

        ss << BaseClass::TAB << BaseClass::TAB << to_build_name << "* " << "build() { " << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return new " << to_build_name << "(*this);" << std::endl;
        ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;

        return ss.str();
    }

    std::string get_destructor() {
        std::stringstream ss;

        typename std::vector<Field>::iterator it;

        ss << "~" << get_name() << "() {" << std::endl;

        for(it = fields.begin() ; it != fields.end() ; ++it) {
            Field& field = *it;
            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "delete " << field.get_name() << ";" << std::endl;
        }

        ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl;

        return ss.str();
    }

    std::string get_setters() {
        std::stringstream ss;

        typename std::vector<Field>::iterator it;

        std::smatch match;
        std::regex num_regex ("^([0-9]*$).*");

        for(it = fields.begin() ; it != fields.end() ; ++it) {
            Field& field = *it;
            std::string length_var = field.get_name() + "_length";
            bool depends_on_var = !std::regex_search (field.get_second(), match, num_regex);

            if(depends_on_var) {
                ss << BaseClass::TAB << BaseClass::TAB << "Builder& " << "set_" << field.get_name() << "(uint8_t* data, std::size_t length) { " << std::endl;
                ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << length_var << " = length;" << std::endl;
            } else {
                ss << BaseClass::TAB << BaseClass::TAB << "Builder& " << "set_" << field.get_name() << "(uint8_t* data) { " << std::endl;
            }

            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << field.get_name() << " = new uint8_t[" << length_var << "];" << std::endl;
            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "memcpy(" << field.get_name() << ", data, " << length_var << ");" << std::endl;
            ss << BaseClass::TAB << BaseClass::TAB << BaseClass::TAB << "return *this;" <<  std::endl;

            ss << BaseClass::TAB << BaseClass::TAB << "}" << std::endl << std::endl;
        }

        return ss.str();
    }

public:

    void set_to_build_name(std::string name) {
        to_build_name = name;
    }

    BuildBaseClass(std::string to_build_name, std::string name) : to_build_name(to_build_name), BaseClass(name) {}

};

#endif //PROTOCOL_COMPILER_BUILDBASECLASS_H
