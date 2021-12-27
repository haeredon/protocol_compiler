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

    ss << "uint8_t* data;";

    for(const Field& field : p_class.get_fields()) {
        ss << "uint16_t " << field.get_name() << "_offset;";
    }

    ss << std::endl << "public:" << std::endl;

    // Constructor
    ss << std::endl << p_class.get_name() << "() {" << std::endl;
    ss << "uint16_t num = 0;";

    for(const Field& field : p_class.get_fields()) {
        if(field.get_is_included() != nullptr) {
            ss << "if(" << field.get_is_included()->to_string() << ") {";
        }

        ss << field.get_name() << "_offset = num;";
        ss << "num +=" << field.get_length()->to_string() << ";";

        if(field.get_is_included() != nullptr) {
            ss << "}";
        }
    }

    ss << "}"; // constructor end

    ss << "}"; // class end
    ss << "}"; // namespace end

    return ss.str();


}

