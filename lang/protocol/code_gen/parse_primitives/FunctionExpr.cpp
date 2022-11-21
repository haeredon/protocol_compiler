//
// Created by skod on 12/12/21.
//

#include "FunctionExpr.h"
#include "FieldExpr.h"
#include<sstream>

void FunctionExpr::add_arg(Expression* expression) {
    args.push_back(expression);
}

std::string FunctionExpr::to_string() const {
    std::stringstream ss;

    ss << "(";

    if(name == "range_equals") {
        std::string base = args[0]->to_string();
        ss << "EndianUtil::range_equals((uint8_t*) &" << args[2]->to_string() << ", data + " << base << ", " << args[1]->to_string() << ")";
    } else if(name == "equals") {
        std::string to_cmp_with = args.front()->to_string();

        for(Expression* expr : args) {

            if(expr == args.front()) {
                continue;
            }

            const FieldExpr* field = static_cast<const FieldExpr*>(expr);
            ss << "EndianUtil::range_equals((uint8_t*) &" << to_cmp_with << ", data + " << field->get_field().get_name() << ".offset, 0," << field->get_field().get_name() << ".length" << ")";

            if(expr != args.back()) {
                ss << " && ";
            }
        }

    } else if(name == "has_not") {

        for(Expression* expr : args) {
            const FieldExpr* field_expr = static_cast<const FieldExpr*>(expr);
            ss << field_expr->get_field().get_name() << ".length == 0";

            if(expr != args.back()) {
                ss << " && ";
            }
        }

    } else if(name == "prefix") {
        throw "Prefix expression not supported anymore, use range_equal instead";
        std::string base = args.front()->to_string();
        ss << "Util::range_equals(" << base << ", &data[num], 0, Util::size_of(" << base << "))";
    } else if(name == "cdata") {
        std::string size = args.front()->to_string();
        ss << "Util::big_to_little(data + num," << size << ");";
    } else {
        throw "No matching function";
    }

    ss << ")";
    return ss.str();
}

void FunctionExpr::set_name(const std::string &name) {
    this->name = name;
}
