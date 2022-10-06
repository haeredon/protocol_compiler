//
// Created by skod on 1/4/22.
//

#include "BuildClass.h"

BuildClass::BuildClass() {

}


std::string BuildClass::class_to_string(Class &p_class) {

    ss << "class Builder {";

    ss << "friend " << p_class.get_name() << ";" << std::endl << std::endl;

    ss << "private:" << std::endl;

    /************************** Private fields **************************************/

    ss << "struct build_field {"
            "uint8_t *data;"
            "std::size_t length;"
            "bool optional;"
            "bool initialized;"
            "build_field(std::size_t length, bool optional, bool initialized) : length(length), optional(optional), initialized(initialized) {}"
        "};";


    ss << "std::size_t size = 0;";

    for(const Field& field : p_class.get_fields()) {
        ss << "build_field "<< field.get_name() << ";";
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            ss << "build_field "<< field.get_name() << ";";
        }
    }



    /************************** Private fields end **************************************/

    ss << std::endl << "public:" << std::endl;


    /*************** Constructor *********************/

    ss << "Builder() : ";

    bool first = true;
    for(const Field& field : p_class.get_fields()) {
        if(!first) {
            ss << ",";
        }

        std::string is_included_str = field.get_is_included() == nullptr ? "false" : "true";
        ss << field.get_name() << "(0, " << is_included_str << ", false)";
        first = false;
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            std::string is_included_str = field.get_is_included() == nullptr ? "false" : "true";
            ss << "," << field.get_name() << "(0, " << is_included_str << ", false)";
        }
    }

    ss << "{}";

    /*************** Constructor End *********************/

    /*************** Destructor *********************/

    ss << "~Builder() {";

    for(const Field& field : p_class.get_fields()) {
        ss << "if(" << field.get_name() << ".initialized) {";
        ss << "delete[] " << field.get_name() << ".data;";
        ss << "}";
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            ss << "if(" << field.get_name() << ".initialized) {";
            ss << "delete[] " << field.get_name() << ".data;";
            ss << "}";
        }
    }

    ss << "}";

    /*************** Destructor End *********************/

    /*************** Getters *********************/

    // [PROTOCOL] build()
    ss << p_class.get_name() << "* " << "build() { ";
    ss << "return new " << p_class.get_name() << "(*this);";
    ss << "}";

    // uint8_t get_data()
    ss << "uint8_t* get_data() {";
    ss << "uint8_t* data = new uint8_t[size];";
    ss << "std::size_t num_consumed = 0;";
    for(const Field& field : p_class.get_fields()) {
        const std::string& name = field.get_name();
        ss << "if(" << name << ".initialized) {";
        ss << "memcpy(data + num_consumed, " << name << ".data, " << name  << ".length);";
        ss << "num_consumed += " << name  << ".length;";
        ss << "}";
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            const std::string& name = field.get_name();
            ss << "if(" << name << ".initialized) {";
            ss << "memcpy(data + num_consumed, " << name << ".data, " << name  << ".length);";
            ss << "num_consumed += " << name  << ".length;";
            ss << "}";
        }
    }

    ss << "return data;";

    ss << "}";

    /*************** Getters End *********************/

    /*************** Setters *********************/

    for(const Field& field : p_class.get_fields()) {
        std::string name = field.get_name();

        ss << "Builder& " << "set_" << field.get_name() << "(std::vector<uint8_t> data) {";
        ss << "return set_" << field.get_name() << "(data.data(), data.size());";
        ss << "}";

        ss << "Builder& " << "set_" << field.get_name() << "(uint8_t* data, std::size_t build_field_length) {";
        ss << "if(" << field.get_name() << ".length != 0) {";
        ss << "size -= " << field.get_name() << ".length;";
        ss << "delete[] " << field.get_name() << ".data;";
        ss << "}";
        ss << field.get_name() << ".data = new uint8_t[build_field_length];";
        ss << "memcpy(" << field.get_name() << ".data, data, build_field_length);";
        ss << field.get_name() << ".initialized = true;";
        ss << field.get_name() << ".length = build_field_length;";
        ss << "size += " << field.get_name() << ".length;";
        ss << "return *this;";
        ss << "}";
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            std::string name = field.get_name();

            ss << "Builder& " << "set_" << field.get_name() << "(std::vector<uint8_t> data) {";
            ss << "return set_" << field.get_name() << "(data.data(), data.size());";
            ss << "}";

            ss << "Builder& " << "set_" << field.get_name() << "(uint8_t* data, std::size_t build_field_length) {";
            ss << "if(" << field.get_name() << ".length != 0) {";
            ss << "size -= " << field.get_name() << ".length;";
            ss << "delete[] " << field.get_name() << ".data;";
            ss << "}";
            ss << field.get_name() << ".data = new uint8_t[build_field_length];";
            ss << "memcpy(" << field.get_name() << ".data, data, build_field_length);";
            ss << field.get_name() << ".initialized = true;";
            ss << field.get_name() << ".length = build_field_length;";
            ss << "size += " << field.get_name() << ".length;";
            ss << "return *this;";
            ss << "}";
        }
    }

    /*************** Setters End *********************/


    ss << "};"; // class end

    return ss.str();
}
