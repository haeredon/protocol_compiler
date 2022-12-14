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
    p_class.visit(this);
    p_class.visit(&initMethod);

    BuildClass build_class;
    private_ss << build_class.class_to_string(p_class);

    return ss_start.str()
        .append(private_ss.str())
        .append(public_ss.str())
        .append(initMethod.to_string())
        .append(ss_end.str());
}

void ProtocolClass::visit(const PrimitiveExpr &x) {
    last_enum_length = stoi(x.to_string());
}

void ProtocolClass::visit(const Switch &x) {
    for (const Case &a_case: x.get_cases()) {
        a_case.get_statement()->visit(this);
    }
}

void ProtocolClass::visit(const While &x) {
    for (const Statement *stmt: x.get_statements()) {
        stmt->visit(this);
    }
}

void ProtocolClass::visit(const FieldExpr &x) {
    throw "FieldExpr should not be possible here. You have done a type mismatch. Maybe you but an enum on a variable length field?.";
}

void ProtocolClass::visit(const Field &x) {
    const std::string &name = x.get_name();

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
    for (const auto &name_to_map: x.get_bitmap().get_name_to_map()) {
        std::string bit_mapping_name = name + "_" + std::get<0>(name_to_map);
        public_ss << "uint64_t get_" << bit_mapping_name << "() {";
        public_ss << "return Util::to_numeric<uint64_t>(&data[" << name << ".offset], " << name << ".length) & "
                  << bit_mapping_name << ";";
        public_ss << "}";
    }

    // enum values
    const std::unordered_map<std::string, std::size_t> &enums = x.get_enumeration().get_enum_to_Val();
    if (enums.size() != 0) {
        public_ss << "enum class " << name << "_enum" << " { ";
        for (const auto &key_pair: x.get_enumeration().get_enum_to_Val()) {
            uint64_t val = std::get<1>(key_pair);
            x.get_length()->visit(this);
            uint64_t enum_value = ProtocolUtil::little_to_big(reinterpret_cast<uint8_t*>(&val), last_enum_length);
            public_ss << std::get<0>(key_pair) << " = " << std::to_string(enum_value) << ",";
        }
        public_ss << "UNKNOWN ";
        public_ss << "};";
    }

    // field getter
    public_ss << "std::vector<uint8_t> get_" << name << "() {";
    public_ss << "return std::vector<uint8_t>(data + " << name << ".offset, data + " << name << ".offset + " << name
              << ".length);";
    public_ss << "}";

}

void ProtocolClass::visit(const Class &x) {
    const std::string &class_name = x.get_name();

    ss_start << "#ifndef PROTOCOL" << "_" << class_name << "_H" << std::endl;
    ss_start << "#define PROTOCOL" << "_" << class_name << "_H" << std::endl;

    ss_start << "#include <vector>" << std::endl;
    ss_start << "#include <string>" << std::endl;
    ss_start << "#include <cstdint>" << std::endl;
    ss_start << "#include <cstring>" << std::endl << std::endl;

    ss_start << "#include \"Util.h\"" << std::endl;
    ss_start << "#include \"EndianUtil.h\"" << std::endl;
    ss_start << "#include \"Protocols.h\"" << std::endl;
    ss_start << "#include \"Config.h\"" << std::endl;
    ss_start << "#include \"Protocol.h\"" << std::endl << std::endl;

    ss_start << "namespace Tunneler {";

    ss_start << "class " << class_name << " : public Protocol " << "{";

    private_ss << std::endl << "private:" << std::endl;

    /************************** Private fields **************************************/
    private_ss << "struct field {"
                  "uint64_t offset;"
                  "uint64_t length;"
                  "};";


    private_ss << "const uint8_t* data;";
    private_ss << "std::size_t size;";

    for (const Statement *stmt: x.get_statements()) {
        stmt->visit(this);
    }

    public_ss << std::endl << "public:" << std::endl;

    // [ProtocolName]()
    public_ss << class_name << "(const uint8_t* data) {";
    public_ss << "init(data);";
    public_ss << "}";

    public_ss << class_name << "(const Builder& builder) {";
    public_ss << "init(builder.get_data());";
    public_ss << "}";

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

    // static Builder get_builder()
    public_ss << "static Builder get_builder() {";
    public_ss << "return Builder();";
    public_ss << "}";

    // get_inner_protocol()
    public_ss << "Protocols get_inner_protocol() {";
    for (auto &field: x.get_next_protocol().get_priorities()) {
        const std::string &field_name = field->get_name();
        const std::unordered_map<std::string, std::size_t> &enums = field->get_enumeration().get_enum_to_Val();
        if (enums.size() != 0) {
            for (const auto &key_pair: field->get_enumeration().get_enum_to_Val()) {
                const std::string &enum_name = std::get<0>(key_pair);
                public_ss << "if(Util::range_equals((uint64_t)(" << field_name << "_enum::" << enum_name
                          << "), data +" << field_name << ".offset, " << field_name << ".length)) {";
                public_ss << "return Protocols::" << enum_name << ";";
                public_ss << "}";
            }
        }
    }
    public_ss << "return Protocols::" << x.get_next_protocol().get_default_next() << ";";
    public_ss << "}";

    ss_end << "};}";
    ss_end << std::endl << "#endif /* PROTOCOL" << "_" << class_name << "_H */" << std::endl;
}

/*********************************** INIT FUNCTION **********************************************/

ProtocolClass::ProtocolClassInit::ProtocolClassInit() {
    ss << "void init(const uint8_t* data) {";
    ss << "this->data = data;";
    ss << "uint16_t num = 0;";
    ss << "uint64_t expr_result = false;";
}


void ProtocolClass::ProtocolClassInit::visit(const Class &x) {
    for (const Statement *stmt: x.get_statements()) {
        stmt->visit(this);
    }
}

void ProtocolClass::ProtocolClassInit::visit(const Field &field_stmt) {
    if (field_stmt.get_is_included() != nullptr) {
        field_stmt.get_is_included()->visit(this);
        ss << "if(expr_result) {";
    }

    ss << field_stmt.get_name() << ".offset = num;";
    ss << "num +=";
    field_stmt.get_length()->visit(this);
    ss << ";";
    ss << field_stmt.get_name() << ".length = num - " << field_stmt.get_name() << ".offset" << ";";

    if (field_stmt.get_is_included() != nullptr) {
        ss << "}";
    }
}

void ProtocolClass::ProtocolClassInit::visit(const While &while_stmt) {
    ss << "while(";
    while_stmt.get_continue_conditional()->visit(this);
    ss << ") {";
    for (const Statement *stmt: while_stmt.get_statements()) {
        stmt->visit(this);
    }
    ss << "}";
}

void ProtocolClass::ProtocolClassInit::visit(const Switch &switch_stmt) {
    ss << "switch(";
    switch_stmt.get_compare_value()->visit(this);
    ss << ") {";
    for (const Case &a_case: switch_stmt.get_cases()) {
        ss << "case ";
        a_case.get_match()->visit(this);
        ss << ":";
        a_case.get_statement()->visit(this);
    }
    ss << "default: throw \"protocol class reached default in switch\";";
    ss << "}";
}

void ProtocolClass::ProtocolClassInit::visit(const FieldExpr &x) {
    const std::string &name = x.get_field()->get_name();
    ss << "EndianUtil::big_to_little(data + " << name << ".offset, " << name << ".length" << ")";
}

void ProtocolClass::ProtocolClassInit::visit(const RangeEqualsExpr &x) {
    ss << "{";
    ss << "uint64_t offset = ";
    x.get_offset()->visit(this);
    ss << ";";

    ss << "uint64_t length = ";
    x.get_length()->visit(this);
    ss << ";";

    ss << "uint64_t value = ";
    x.get_value()->visit(this);
    ss << ";";

    ss << "expr_result = EndianUtil::range_equals((uint8_t*)&value, data + offset, length);";
    ss << "}";
}

void ProtocolClass::ProtocolClassInit::visit(const EqualsExpr &x) {
    Expression *to_cmp_with = x.get_args().front();
    const std::vector<Expression *> &args = x.get_args();

    ss << "{";

    ss << "uint64_t to_cmp_with = ";
    to_cmp_with->visit(this);
    ss << ";";

    ss << "expr_result = ";

    for (Expression *expr: args) {

        if (expr == args.front()) {
            continue;
        }
        ss << "to_cmp_with == ";
        expr->visit(this);

        if (expr != args.back()) {
            ss << " && ";
        }
    }

    ss << ";}";
}

void ProtocolClass::ProtocolClassInit::visit(const HasNotExpr &x) {
    const std::vector<FieldExpr *> &args = x.get_args();

    ss << "{";

    ss << "expr_result = ";

    for (FieldExpr *expr: args) {
        ss << expr->get_field()->get_name() << ".length == 0";

        if (expr != args.back()) {
            ss << " && ";
        }
    }


    ss << ";}";
}

void ProtocolClass::ProtocolClassInit::visit(const SubRangeExpr &x) {
    ss << "{";

    ss << "expr_result = EndianUtil::big_to_little(data + num,";
    x.get_arg()->visit(this);
    ss << ")";

    ss << ";}";
}

void ProtocolClass::ProtocolClassInit::visit(const OperatorExpr &x) {
    x.get_left_expr()->visit(this);
    ss << "expr_result = expr_result ";
    ss << x.get_operator();
    x.get_right_expr()->visit(this);
    ss << ";";
}

void ProtocolClass::ProtocolClassInit::visit(const PrimitiveExpr &x) {
    ss << "((uint64_t)";
    ss << x.to_string() << ")";
}

std::string ProtocolClass::ProtocolClassInit::to_string() {
    ss << "size = num;";
    ss << "}";
    return ss.str();
}
