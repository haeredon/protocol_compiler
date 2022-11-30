//
// Created by skod on 12/15/21.
//


#include "ProtocolClass.h"
#include "BuildClass.h"
#include "ProtocolUtil.h"
#include "Util.h"

#include <iostream>
#include <valarray>
#include <cctype>
#include <arpa/inet.h>


ProtocolClass::ProtocolClass() {

}


std::string ProtocolClass::class_to_string(Class &p_class) {
//
//    /************************** Builder **************************************/
//
//    BuildClass build_class;
//    ss << build_class.class_to_string(p_class);
//
//    /************************** Builder end **************************************/
//
//    /************************** Private fields end **************************************/
//
//    ss << std::endl << "public:" << std::endl;
//
//
//    /*************** Constructor *********************/

//
//    // [ProtocolName](Builder& builder)
//    ss << p_class.get_name() << "(Builder& builder) {";
//    ss << "init(builder.get_data());";
//    ss << "}";
//
//    /*************** Constructor End *********************/
//
//    /*************** Getters *********************/
//
//

//
//    // static Builder get_builder()
//    ss << "static Builder get_builder() {";
//    ss << "return Builder();";
//    ss << "}";
//

//
//
//    /*************** Getters End *********************/







    return private_ss.str();


}

void ProtocolClass::visit(const PrimitiveExpr &x) {
    *target_ss << x.to_string();
}

void ProtocolClass::visit(const OperatorExpr &x) {

}

void ProtocolClass::visit(const FunctionExpr &x) {

}

void ProtocolClass::visit(const FieldExpr &x) {

}

void ProtocolClass::visit(const DotExpression &x) {

}

void ProtocolClass::visit(const Switch &x) {
    for(const Case& a_case: x.get_cases()) {
        a_case.get_statement()->visit(this);
    }
}

void ProtocolClass::visit(const While &x) {
    for(const Statement* stmt: x.get_statements()) {
        stmt->visit(this);
    }
}

void ProtocolClass::visit(const Field &x) {
    const std::string& name = x.get_name();

    private_ss << "field " << name << ";";

    // bitmap masking values
    for (const auto &name_to_map: x.get_bitmap().get_name_to_map()) {
        std::string range_name = std::get<0>(name_to_map);
        std::tuple<std::size_t, std::size_t> range = std::get<1>(name_to_map);;
        uint64_t mask = std::pow(2, std::get<1>(range)) +
                        (std::pow(2, std::get<1>(range)) - std::pow(2, std::get<0>(range)));
        public_ss << "static const uint64_t " << name << "_" << range_name << "= 0x" << std::hex << mask << ";"
           << std::endl;
    }

    // bitmap getters
    for(const auto& name_to_map : x.get_bitmap().get_name_to_map()) {
        std::string bit_mapping_name = name + "_" + std::get<0>(name_to_map);
        public_ss << "uint64_t get_" << bit_mapping_name << "() {";
        public_ss << "return Util::to_numeric<uint64_t>(&data[" << name << ".offset], " << name << ".length) & " <<  bit_mapping_name << ";";
        public_ss << "}";
    }

    // enum values
    const std::unordered_map<std::string, std::size_t>& enums = x.get_enumeration().get_enum_to_Val();
    if(enums.size() != 0) {
        public_ss << "enum class " << name << "_enum" << " { ";
        for(const auto& key_pair : x.get_enumeration().get_enum_to_Val()) {
            uint64_t val = std::get<1>(key_pair);
            public_ss << std::get<0>(key_pair) << " = Util::little_to_big(" << val << ", ";
            target_ss = &public_ss;
            x.visit(this);
            public_ss << ")";
            public_ss << ", ";
        }
        public_ss << "UNKNOWN ";
        public_ss << "};";
    }

    // field getter
    public_ss << "std::vector<uint8_t> get_" << name << "() {";
    public_ss << "return std::vector<uint8_t>(data + " << name << ".offset, data + " << name << ".offset + " << name << ".length);";
    public_ss << "}";

}

void ProtocolClass::visit(const Class &x) {
    const std::string& class_name = x.get_name();

    ss << "#ifndef PROTOCOL" << "_" << class_name << "_H" << std::endl;
    ss << "#define PROTOCOL" << "_" << class_name<< "_H" << std::endl;

    ss << "#include <vector>" << std::endl;
    ss << "#include <string>" << std::endl;
    ss << "#include <cstdint>" << std::endl;
    ss << "#include <cstring>" << std::endl << std::endl;

    ss << "#include \"Util.h\"" << std::endl;
    ss << "#include \"Protocols.h\"" << std::endl;
    ss << "#include \"Config.h\"" << std::endl;
    ss << "#include \"Protocol.h\"" << std::endl << std::endl;

    ss << "namespace Tunneler {";

    ss << "class " << class_name << " : public Protocol " << "{";

    private_ss << std::endl << "private:" << std::endl;

    /************************** Private fields **************************************/
    private_ss << "struct field {"
          "uint64_t offset;"
          "uint64_t length;"
          "};";


    private_ss << "const uint8_t* data;";
    private_ss << "std::size_t size;";

    for(const Statement* stmt : x.get_statements()) {
        stmt->visit(this);
    }

    public_ss << std::endl << "public:" << std::endl;

    // [ProtocolName]()
    public_ss << class_name << "(const uint8_t* data) {";
    public_ss << "init(data);";
    public_ss << "}"; // constructor end

    // Protocols get_protocol_type();
    public_ss << "Protocols get_protocol_type() {";
    public_ss << "return Protocols::" << ProtocolParser::Util::to_upper(class_name) << ";";
    public_ss << "}";

    // std::string to_string();
    public_ss << "std::string to_string() {";
    public_ss << "return Util::binary_to_hex_pretty_print(data, size);";
    public_ss << "}";

    // std::size_t get_size();
    public_ss << "std::size_t get_size() {";
    public_ss << "return size;";
    public_ss << "}";

    // std::vector<uint8_t> to_data();
    public_ss << "std::vector<uint8_t> to_data() {";
    public_ss << "return std::vector<uint8_t>(data, data + size);";
    public_ss << "}";

    // get_inner_protocol()
    public_ss << "Protocols get_inner_protocol() {";
    for(auto& field : x.get_next_protocol().get_priorities()) {
        const std::string& field_name = field->get_name();
        const std::unordered_map<std::string, std::size_t>& enums = field->get_enumeration().get_enum_to_Val();
        if(enums.size() != 0) {
            for(const auto& key_pair : field->get_enumeration().get_enum_to_Val()) {
                const std::string& enum_name = std::get<0>(key_pair);
                public_ss << "if(Util::range_equals(static_cast<std::size_t>(" << field_name << "_enum::" << enum_name << "), &data[" << field_name << ".offset], 0," << field_name << ".length)) {";
                public_ss << "return Protocols::" << enum_name << ";";
                public_ss << "}";
            }
        }
    }
    public_ss << "return Protocols::" << x.get_next_protocol().get_default_next() << ";";
    public_ss << "}";


    // TODO: concatinate streams

    ss << "};"; // class end
    ss << "}"; // namespace end

    ss << std::endl << "#endif /* PROTOCOL" << "_" << class_name << "_H */" << std::endl;
}



