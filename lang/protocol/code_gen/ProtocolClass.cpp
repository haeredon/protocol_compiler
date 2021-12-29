//
// Created by skod on 12/15/21.
//


#include "ProtocolClass.h"

#include <iostream>

ProtocolClass::ProtocolClass() {

}

void ProtocolClass::prepare_fields(Class &p_class) {
    for(Field& field : p_class.get_fields()) {
//        field.set_to_string_handler(*this);
//        ss << "num +=" << field.get_length()->to_string() << ";";
    }
}


std::string ProtocolClass::field_to_string_handler(const Field& field) {
    return "field_to_string_handler()";
}

std::string ProtocolClass::class_to_string(Class &p_class) {
    prepare_fields(p_class);

    //for(const Field& field : p_class.get_fields()) {
      //  std::cout << "uint16_t " << &field << " _offset;" << std::endl;
    //}

    ss << "#ifndef PROTOCOL" << "_" << p_class.get_name() << "_H" << std::endl;
    ss << "#define PROTOCOL" << "_" << p_class.get_name() << "_H" << std::endl;

    ss << "#include <vector>" << std::endl;
    ss << "#include <string>" << std::endl;
    ss << "#include <cstring>" << std::endl << std::endl;

    ss << "#include \"Util.h\"" << std::endl;
    ss << "#include \"Protocols.h\"" << std::endl;
    ss << "#include \"Config.h\"" << std::endl;
    ss << "#include \"Protocol.h\"" << std::endl << std::endl;

    ss << "namespace Tunneler {";

    ss << "class " << p_class.get_name() << " : public Protocol " << "{";

    ss << "private:" << std::endl;

    /************************** Private fields **************************************/
    ss << "uint8_t* data;";

    for(const Field& field : p_class.get_fields()) {
        ss << "field " << field.get_name() << ";";
    }

    for(const FieldGroup& group : p_class.get_field_groups()) {
        for(const Field& field : group.get_fields()) {
            ss << "field " << field.get_name() << ";";
        }
    }

    /************************** Private fields end **************************************/

    ss << std::endl << "public:" << std::endl;


    /*************** Constructor *********************/
    ss << std::endl << p_class.get_name() << "() {" << std::endl;
    ss << "uint16_t num = 0;";

    // Fields
    for(const Field& field : p_class.get_fields()) {

        if(field.get_is_included() != nullptr) {
            ss << "if(" << field.get_is_included()->to_string() << ") {";
        }

        ss << field.get_name() << ".offset = num;";
        ss << "num +=" << field.get_length()->to_string() << ";";
        ss << field.get_name() << ".length = num - " << field.get_name() << ".offset" << ";";

        if(field.get_is_included() != nullptr) {
            ss << "}";
        }
    }

    // Field Groups
    for(const FieldGroup& group : p_class.get_field_groups()) {
        ss << "{";
        ss << "uint16_t num_read = 0;";

        ss << "while(" << group.get_is_continue()->to_string() << ") {";

        bool first = true;
        for(const Field& field : group.get_fields()) {

            if(field.get_is_included() != nullptr) {
                ss << (first ? "if" : "else if") << "(" << field.get_is_included()->to_string() << ") {";
            }

            ss << field.get_name() << ".offset = num;";
            ss << "num +=" << field.get_length()->to_string() << ";";
            ss << "num_read +=" << field.get_length()->to_string() << ";";
            ss << field.get_name() << ".length = num - " << field.get_name() << ".offset" << ";";

            if(field.get_is_included() != nullptr) {
                ss << "}";
            }
        }

        ss << "}";
        ss << "}";
    }

    ss << "}"; // constructor end
    /*************** Constructor End *********************/

    ss << "}"; // class end
    ss << "}"; // namespace end

    return ss.str();


}

