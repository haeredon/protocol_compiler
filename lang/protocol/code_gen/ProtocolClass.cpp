//
// Created by skod on 12/15/21.
//


#include "ProtocolClass.h"


ProtocolClass::ProtocolClass() {

}

std::string ProtocolClass::class_to_string(const Class &p_class) {
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
        ss << field.get_name() << "_offset = num;";
        ss << "num += SOME_NUMBER;";
    }

    ss << "}"; // constructor end

    ss << "}"; // class end
    ss << "}"; // namespace end

    return ss.str();


}
