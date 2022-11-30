//
// Created by skod on 11/25/22.
//

#include "ProtocolClass.h"



ProtocolClassInit::ProtocolClassInit() {
    ss << "void init(const uint8_t* data) {";
    ss << "this->data = data;";
    ss << "uint16_t num = 0;";
}


void ProtocolClassInit::visit(const Class &x) {
    for(const Statement* stmt : x.get_statements()) {
        stmt->visit(this);
    }
}

void ProtocolClassInit::visit(const Field& field_stmt) {
    if(field_stmt.get_is_included() != nullptr) {
        ss << "if(";
        field_stmt.get_is_included()->visit(this);
        ss << ") {";
    }

    ss << field_stmt.get_name() << ".offset = num;";
    ss << "num +=";
    field_stmt.get_length()->visit(this);
    ss << ";";
    ss << field_stmt.get_name() << ".length = num - " << field_stmt.get_name() << ".offset" << ";";

    if(field_stmt.get_is_included() != nullptr) {
        ss << "}";
    }
}

void ProtocolClassInit::visit(const While& while_stmt) {

}

void ProtocolClassInit::visit(const Switch& switch_stmt) {

}

void ProtocolClassInit::visit(const DotExpression &x) {}

void ProtocolClassInit::visit(const FieldExpr &x) {
    const std::string& name = x.get_field()->get_name();
    ss << "Util::big_to_little(data + " << name << ".offset, " << name << ".length" << ")";
}

void ProtocolClassInit::visit(const FunctionExpr &x) {
    const std::vector<Expression*>& args = x.get_args();
    const std::string& name = x.get_name();

    ss << "(";

    if(name == "range_equals") {
        ss << "EndianUtil::range_equals((uint8_t*) &";
        args[2]->visit(this);
        ss << ", data + ";
        args[0]->visit(this);
        ss << ", ";
        args[1]->visit(this);
        ss << ")";
    } else if(name == "equals") {
        Expression* to_cmp_with = args.front();

        for(Expression* expr : args) {

            if(expr == args.front()) {
                continue;
            }

            const FieldExpr* field = static_cast<const FieldExpr*>(expr);
            const std::string& field_name = field->get_field()->get_name();
            ss << "EndianUtil::range_equals((uint8_t*) &";
            to_cmp_with->visit(this);
            ss << ", data + " << field_name << ".offset, 0," << field_name<< ".length" << ")";

            if(expr != args.back()) {
                ss << " && ";
            }
        }

    } else if(name == "has_not") {

        for(Expression* expr : args) {
            const FieldExpr* field_expr = static_cast<const FieldExpr*>(expr);
            ss << field_expr->get_field()->get_name() << ".length == 0";

            if(expr != args.back()) {
                ss << " && ";
            }
        }

    } else if(name == "cdata") {
        ss << "Util::big_to_little(data + num,";
        args.front()->visit(this);
        ss << ");";
    } else {
        throw "No matching function";
    }

    ss << ")";
}

void ProtocolClassInit::visit(const OperatorExpr &x) {
    x.get_left_expr()->visit(this);
    ss << x.get_operator();
    x.get_right_expr()->visit(this);
}

void ProtocolClassInit::visit(const PrimitiveExpr &x) {
    ss << x.to_string();
}

std::string ProtocolClassInit::to_string() {
    ss << "size = num;";
    ss << "}";
    return ss.str();
}
