//
// Created by skod on 11/25/22.
//

#include "ProtocolClass.h"



ProtocolClassInit::ProtocolClassInit() {
    ss << "void init(const uint8_t* data) {";
    ss << "this->data = data;";
    ss << "uint16_t num = 0;";
}

void ProtocolClassInit::visit(const While& while_stmt) {

}

void ProtocolClassInit::visit(const Field& field_stmt) {
    if(field_stmt.get_is_included() != nullptr) {
        ss << "if(" << field_stmt.get_is_included()->to_string() << ") {";
    }

    field_stmt.get_length()->visit(this);

    ss << field_stmt.get_name() << ".offset = num;";
    ss << "num +=" << field_stmt.get_length()->to_string() << ";";
    ss << field_stmt.get_name() << ".length = num - " << field_stmt.get_name() << ".offset" << ";";

    if(field_stmt.get_is_included() != nullptr) {
        ss << "}";
    }
}

void ProtocolClassInit::visit(const Switch& switch_stmt) {

}

void ProtocolClassInit::visit(const DotExpression &x) {

}

void ProtocolClassInit::visit(const FieldExpr &x) {

}

void ProtocolClassInit::visit(const FunctionExpr &x) {

}

void ProtocolClassInit::visit(const OperatorExpr &x) {

}

void ProtocolClassInit::visit(const PrimitiveExpr &x) {

}

std::string ProtocolClassInit::to_string() {
    ss << "size = num;";
    ss << "}";
    return ss.str();
}

