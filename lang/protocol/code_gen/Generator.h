//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_GENERATOR_H
#define PARSER_CODE_GEN_GENERATOR_H

#include "CodeGen.h"
#include "BaseClass.h"
//#include "Field.h"
#include "BuildClass.h"
#include "parse_primitives/Class.h"
#include "parse_primitives/FieldGroup.h"
#include "parse_primitives/Field.h"
#include "parse_primitives/Bitmap.h"
#include "parse_primitives/Expression.h"
#include "parse_primitives/Enumeration.h"
#include "parse_primitives/Property.h"
#include "parse_primitives/Primitive.h"
#include "parse_primitives/Function.h"
#include "parse_primitives/DotExpression.h"
#include "parse_primitives/Operator.h"
#include "../Tokens.h"
#include "ProtocolClass.h"

#include <vector>
#include <iostream>
#include <algorithm>

template<class RET_T>
class Generator : public ProtocolParser::CodeGen<RET_T> {

private:

    Class parsed_class;

public:

    std::vector<std::string> generate(ProtocolParser::Node* ast) {
        std::vector<std::string> classes;

        for(ProtocolParser::Node* node : ast->get_children()) {
            ProtocolClass protocol_class;
            classes.push_back(protocol_class.class_to_string(parse_class(node)));
        }

        return classes;
    }

    Class parse_class(ProtocolParser::Node* ast) {

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "NAME") {
                std::string name = node->get_children().front()->get_value();
                parsed_class.set_name(name);
            } else if(attr_name == "FIELDS") {
                parse_fields(node);
            } else if(attr_name == "PROPERTIES") {
                parse_properties(node);
            }
        }

        return parsed_class;
    }

    void parse_fields(ProtocolParser::Node* ast) {

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "FIELD") {
                parsed_class.add_field(parse_field(node));
            } else if(attr_name == "FIELD_GROUP") {
                parsed_class.add_field_group(parse_field_group(node));
            }
        }

    }

    void parse_properties(ProtocolParser::Node* ast) {

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "PROPERTY") {
                parsed_class.add_property(parse_property(node));
            }
        }
    }

    Field parse_field(ProtocolParser::Node* ast) {
        Field field;

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "NAME") {
                std::string name = node->get_children().front()->get_value();
                field.set_name(name);
            } else if(attr_name == "LENGTH") {
                Expression* length_expr = parse_expression(node->get_children().front());
                field.set_length(length_expr);
            } else if(attr_name == "CONDITIONAL") {
                Expression* is_included_expr = parse_expression(node->get_children().front());
                field.set_is_included(is_included_expr);
            } else if(attr_name == "MAP") {
                field.set_bitmap(parse_bitmap(node));
            } else if(attr_name == "ENUM") {
                field.set_enumeration(parse_enumeration(node));
            }
        }

        return field;
    }

    FieldGroup parse_field_group(ProtocolParser::Node* ast) {
        FieldGroup field_group;

        ProtocolParser::Node* cond_expr = ast->get_children().front();
        field_group.set_is_continue(parse_expression(cond_expr));

        std::vector<ProtocolParser::Node*> fields = ast->get_children().back()->get_children();
        for(ProtocolParser::Node* node : fields) {
            field_group.add_field(parse_field(ast));
        }

        return field_group;
    }

    Property parse_property(ProtocolParser::Node* ast) {
        Property property;

        std::string name = ast->get_children().front()->get_children().front()->get_value();
        property.set_name(name);

        std::vector<ProtocolParser::Node*>& args = ast->get_children().back()->get_children();
        for(ProtocolParser::Node* node : args) {
            property.add_arg(node->get_value());
        }

        return property;
    }

    Bitmap parse_bitmap(ProtocolParser::Node* ast) {
        Bitmap bitmap;
        std::size_t num_taken = 0;

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string name = node->get_children().front()->get_children().front()->get_value();
            std::size_t value = stoi(node->get_children().back()->get_children().front()->get_value()); // TODO: can be an expression in the future

            bitmap.append_mapping(name, std::tuple(num_taken, num_taken + value - 1));

            num_taken += value;
        }

        return bitmap;
    };

    Enumeration parse_enumeration(ProtocolParser::Node* ast) {
        Enumeration enumeration;

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string name = node->get_children().front()->get_children().front()->get_value();
            std::size_t value = stoi(node->get_children().back()->get_children().front()->get_value());

            enumeration.add_val(name, value);
        }

        return enumeration;
    };

    Expression* parse_expression(ProtocolParser::Node* ast) {
        std::string value = ast->get_value();

        std::vector<ProtocolParser::Node*>& children = ast->get_children();
        Expression* expression = new Expression();

        if(ast->get_children().size() == 2) {
            expression->set_left_expr(parse_expression(children.front()));
            expression->set_right_expr(parse_expression(children.back()));
        }

        if(ProtocolParser::Tokens::op_precedence.contains(value)) {
            expression->set_expr_element(Operator(value));
        } else if(value == "FUN") {
            expression->set_expr_element(parse_function(ast));
        } else if(parsed_class.has_field(value)) {
            Field field = parsed_class.get_field(value);

            if(children.size() == 1 && children.front()->get_value() == "DOT") {
                expression->set_expr_element(parse_dot_expression(ast));
            } else {
                expression->set_expr_element(field);
            }
        } else {
            expression->set_expr_element(Primitive(value));
        }

        return expression;
    }

    Function parse_function(ProtocolParser::Node* ast) {
        std::vector<ProtocolParser::Node*>& children = ast->get_children();

        Function function;

        for(ProtocolParser::Node* node : children.back()->get_children()) {
            function.add_arg(parse_expression(node));
        }

        return function;
    }

    DotExpression parse_dot_expression(ProtocolParser::Node* ast) {
        std::vector<ProtocolParser::Node*>& children = ast->get_children();

        DotExpression dot_expression;
        dot_expression.set_top(&parsed_class.get_field(ast->get_value()));

        while (!ast->get_children().empty()) {
            ast = ast->get_children().front()->get_children().front();
            dot_expression.add_chain_element(ast->get_value());
        }

        return dot_expression;
    }

};


#endif //PARSER_CODE_GEN_GENERATOR_H
