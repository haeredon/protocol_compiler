//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_PARSECLASS_H
#define PARSER_CODE_GEN_PARSECLASS_H

#include "ProtocolBaseClass.h"
#include "BuildClass.h"

#include<sstream>

class ProtocolClass : public ProtocolBaseClass {

private:

    BuildClass* buildClass;

public:

    ProtocolClass(BuildClass* buildClass) : ProtocolBaseClass("DEFAULT"), buildClass(buildClass) {

    }

    ProtocolClass() : ProtocolBaseClass("DEFAULT") {

    }

    std::string to_string() {
        std::stringstream ss;

        ss << "#ifndef PROTOCOL" << "_" << this->get_name() << "_H" << std::endl;
        ss << "#define PROTOCOL" << "_" << this->get_name() << "_H" << std::endl << std::endl;

        ss << "#include <vector>" << std::endl;
        ss << "#include <cstring>" << std::endl << std::endl;

        ss << "#include \"Util.h\"" << std::endl;
        ss << "#include \"BitUtility.h\"" << std::endl;
        ss << "#include \"Protocols.h\"" << std::endl;
        ss << "#include \"Protocol.h\"" << std::endl << std::endl;

        ss << "namespace Tunneler {" << std::endl << std::endl;

        ss << BaseClass::TAB << "class " << this->get_name() << " " << this->get_inheritance() << " { " << std::endl << std::endl;

        ss << "private: " << std::endl << std::endl;

        ss << BaseClass::TAB << this->get_privates() << std::endl << std::endl;

        ss << BaseClass::TAB << "public:" << std::endl << std::endl;

        ss << BaseClass::TAB << buildClass->to_string() << std::endl << std::endl;

        ss << BaseClass::TAB << this->get_constructor() << std::endl << std::endl;

        ss << BaseClass::TAB << this->get_getters() << std::endl << std::endl;

        ss << BaseClass::TAB << "};" << std::endl << std::endl;

        ss << "}" << std::endl << std::endl;

        ss << "#endif /* PROTOCOL" << "_" << this->get_name() << "_H */" << std::endl;

        return ss.str();
    }

};


#endif //PARSER_CODE_GEN_PARSECLASS_H
