//
// Created by skod on 1/4/22.
//

#include "BuildClass.h"

BuildClass::BuildClass() {

}


std::string BuildClass::class_to_string(Class &p_class) {
    p_class.visit(this);

    return start_ss.str()
        .append(private_ss.str())
        .append(public_ss.str())
        .append(constructor_ss.str())
        .append(destructor_ss.str())
        .append(get_data_ss.str())
        .append(end_ss.str());
}

void BuildClass::visit(const PrimitiveExpr &x) {
    ClassVisitor::visit(x);
}

void BuildClass::visit(const Switch &x) {
    for (const Case &a_case: x.get_cases()) {
        a_case.get_statement()->visit(this);
    }
}

void BuildClass::visit(const While &x) {
    for (const Statement *stmt: x.get_statements()) {
        stmt->visit(this);
    }
}

void BuildClass::visit(const Field &x) {
    const std::string& field_name = x.get_name();

    private_ss << "build_field " << field_name << ";";

    std::string is_included_str = x.get_is_included() == nullptr ? "false" : "true";
    constructor_ss << x.get_name() << "(0, " << is_included_str << ", false),";

    destructor_ss << "if(" << field_name << ".initialized) {";
    destructor_ss << "delete[] " << field_name << ".data;";
    destructor_ss << "}";

    get_data_ss << "if(" << field_name << ".initialized) {";
    get_data_ss << "memcpy(data + num_consumed, " << field_name << ".data, " << field_name << ".length);";
    get_data_ss << "num_consumed += " << field_name << ".length;";
    get_data_ss << "}";

    public_ss << "Builder& " << "set_" << field_name << "(std::vector<uint8_t> data) {";
    public_ss << "return set_" << field_name<< "(data.data(), data.size());";
    public_ss << "}";

    public_ss << "Builder& " << "set_" << field_name << "(uint8_t* data, std::size_t build_field_length) {";
    public_ss << "if(" << field_name<< ".length != 0) {";
    public_ss << "size -= " << field_name << ".length;";
    public_ss << "delete[] " << field_name << ".data;";
    public_ss << "}";
    public_ss << field_name << ".data = new uint8_t[build_field_length];";
    public_ss << "memcpy(" << field_name << ".data, data, build_field_length);";
    public_ss << field_name << ".initialized = true;";
    public_ss << field_name << ".length = build_field_length;";
    public_ss << "size += " << field_name << ".length;";
    public_ss << "return *this;";
    public_ss << "}";
}

void BuildClass::visit(const Class &x) {
    const std::string& class_name = x.get_name();

    start_ss << "class Builder {";
    start_ss << "friend " << class_name << ";" << std::endl << std::endl;

    end_ss << "};";

    private_ss << "private:" << std::endl;
    private_ss << "struct build_field {"
            "uint8_t *data;"
            "std::size_t length;"
            "bool optional;"
            "bool initialized;"
            "build_field(std::size_t length, bool optional, bool initialized) : length(length), optional(optional), initialized(initialized) {}"
        "};";
    private_ss << "std::size_t size = 0;";

    public_ss << std::endl << "public:" << std::endl;

    constructor_ss << "Builder() : ";
    destructor_ss << "~Builder() {";

    get_data_ss << "uint8_t* get_data() const {";
    get_data_ss << "uint8_t* data = new uint8_t[size];";
    get_data_ss << "std::size_t num_consumed = 0;";

    for(const Statement* stmt : x.get_statements()) {
        stmt->visit(this);
    }

    destructor_ss << "}";
    constructor_ss.seekp(-1, std::ios_base::end); // remove last comma in initializer list
    constructor_ss << "{}";

    get_data_ss << "return data;";
    get_data_ss << "}";

    // [PROTOCOL] build()
    public_ss << class_name << "* " << "build() { ";
    public_ss << "return new " << class_name << "(*this);";
    public_ss << "}";
}
