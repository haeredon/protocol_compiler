//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_GENERATOR_H
#define PARSER_CODE_GEN_GENERATOR_H

#include "CodeGen.h"

//#include "Field.h"
#include "BuildClass.h"
#include "parse_primitives/Class.h"
#include "parse_primitives/While.h"
#include "parse_primitives/Switch.h"
#include "parse_primitives/Case.h"
#include "parse_primitives/Field.h"
#include "parse_primitives/Bitmap.h"
#include "parse_primitives/Expression.h"
#include "parse_primitives/Enumeration.h"
#include "parse_primitives/PrimitiveExpr.h"
#include "parse_primitives/FunctionExpr.h"
#include "parse_primitives/DotExpression.h"
#include "parse_primitives/OperatorExpr.h"
#include "../Tokens.h"
#include "ProtocolClass.h"
#include "parse_primitives/FieldExpr.h"

#include <vector>
#include <iostream>
#include <algorithm>

template<class RET_T>
class Generator : public ProtocolParser::CodeGen<RET_T> {


public:

    std::vector<std::pair<std::string, std::string>> generate(ProtocolParser::Node* ast) {
        std::vector<std::pair<std::string, std::string>> classes;

        for(ProtocolParser::Node* node : ast->get_children()) {
            ProtocolClass protocol_class;
            Class new_class = parse_class(node);
            classes.push_back(std::make_pair(node->get_children().front()->get_children().front()->get_value(),protocol_class.class_to_string(new_class)));
        }

        return classes;
    }

    Class parse_class(ProtocolParser::Node* ast) {
        Class parsed_class;

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "NAME") {
                std::string name = node->get_children().front()->get_value();
                parsed_class.set_name(name);
            } else if(attr_name == "FIELDS") {
                parse_fields(node, parsed_class);
            } else if(attr_name == "PROPERTIES") {
                parse_properties(node, parsed_class);
            }
        }

        return parsed_class;
    }

    void parse_fields(ProtocolParser::Node* ast, Class& parsed_class) {

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "FIELD") {
                parsed_class.add_statement(parse_field(node, parsed_class));
            } else if(attr_name == "WHILE") {
                parsed_class.add_statement(parse_while(node, parsed_class));
            } else if(attr_name == "SWITCH") {
//                parsed_class.add_switch(parse_field_group(node, parsed_class));
            }
        }

    }

    void parse_properties(ProtocolParser::Node* ast, Class& parsed_class) {

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_children().front()->get_children().front()->get_value();

            if(attr_name == "NEXT_PROTOCOL") {
                parsed_class.set_next_protocol(parse_next_protocol(node, parsed_class));
            }
        }
    }

    Statement* parse_while(ProtocolParser::Node* ast, Class& parsed_class) {
        Expression* continue_conditional = parse_expression(ast->get_children().front(), parsed_class);
        std::list<Statement*> stmts;

        for(ProtocolParser::Node* node : ast->get_children().back()->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "FIELD") {
                stmts.push_back(parse_field(node, parsed_class));
            } else if(attr_name == "WHILE") {
                stmts.push_back(parse_while(node, parsed_class));
            } else if(attr_name == "SWITCH") {
                stmts.push_back(parse_switch(node, parsed_class));
            }
        }


        return new While(continue_conditional, std::move(stmts));
    }

    Statement* parse_switch(ProtocolParser::Node* ast, Class& parsed_class) {
        Expression* compare_value = parse_expression(ast->get_children().front(), parsed_class);
        std::list<Case> cases;

        ProtocolParser::Node* cases_node = ast->get_children().back();
        for(ProtocolParser::Node* node : cases_node->get_children()) {
            std::string attr_name = node->get_value();

            Expression* match = parse_expression(node->get_children().front(), parsed_class);
            cases.emplace_back(match, parse_field(node->get_children().back(), parsed_class));
        }

        return new Switch(compare_value, std::move(cases));
    }

    Field* parse_field(ProtocolParser::Node* ast, Class& parsed_class) {
        Field* field = new Field();

        for(ProtocolParser::Node* node : ast->get_children()) {
            std::string attr_name = node->get_value();

            if(attr_name == "NAME") {
                std::string name = node->get_children().front()->get_value();
                field->set_name(name);
            } else if(attr_name == "LENGTH") {
                Expression* length_expr = parse_expression(node->get_children().front(), parsed_class);
                field->set_length(length_expr);
            } else if(attr_name == "CONDITIONAL") {
                Expression* is_included_expr = parse_expression(node->get_children().front(), parsed_class);
                field->set_is_included(is_included_expr);
            } else if(attr_name == "MAP") {
                field->set_bitmap(parse_bitmap(node));
            } else if(attr_name == "ENUM") {
                field->set_enumeration(parse_enumeration(node));
            }
        }

        parsed_class.add_variable(field->get_name(), field);
        return field;
    }

    NextProtocol parse_next_protocol(ProtocolParser::Node* ast, Class& parsed_class) {
        NextProtocol next_protocol;

        std::vector<ProtocolParser::Node*>& args = ast->get_children().back()->get_children();
        for(ProtocolParser::Node* node : args) {
            std::string& name = node->get_value();
            if(parsed_class.has_variable(name)) {
                next_protocol.add_next(parsed_class.get_variable(name));
            } else {
                next_protocol.set_default_next(name);
            }
        }

        return next_protocol;
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

    template<class FIELD_HANDLER_T = FieldExpr>
    Expression* parse_expression(ProtocolParser::Node* ast, Class& parsed_class) {
        std::string value = ast->get_value();

        std::vector<ProtocolParser::Node*>& children = ast->get_children();

        if(ProtocolParser::Tokens::op_precedence.contains(value)) {
            OperatorExpr* operator_expr = new OperatorExpr(
                    value,
                    parse_expression<FIELD_HANDLER_T>(children.front(), parsed_class),
                    parse_expression<FIELD_HANDLER_T>(children.back(), parsed_class));
            return operator_expr;
        } else if(value == "FUN") {
            return parse_function(ast, parsed_class);
        } else if(parsed_class.has_variable(value)) {
            Field* field = parsed_class.get_variable(value);

            if(children.size() == 1 && children.front()->get_value() == "DOT") {
//                expression->set_expr_element(parse_dot_expression(ast));
                return nullptr;
            } else {
                return new FIELD_HANDLER_T(field);
            }
        } else {
            return new PrimitiveExpr(value);
        }
    }

    FunctionExpr* parse_function(ProtocolParser::Node* ast, Class& parsed_class) {
        std::vector<ProtocolParser::Node*>& children = ast->get_children();

        FunctionExpr* function = new FunctionExpr();

        function->set_name(children.front()->get_children().front()->get_value());

        for(ProtocolParser::Node* node : children.back()->get_children()) {
            function->add_arg(parse_expression(node, parsed_class));
        }

        return function;
    }

//    DotExpression* parse_dot_expression(ProtocolParser::Node* ast) {
//        std::vector<ProtocolParser::Node*>& children = ast->get_children();
//
//        DotExpression* dot_expression = new DotExpression();
//        dot_expression->set_top(&parsed_class.get_field(ast->get_value()));
//
//        while (!ast->get_children().empty()) {
//            ast = ast->get_children().front()->get_children().front();
//            dot_expression->add_chain_element(ast->get_value());
//        }
//
//        return dot_expression;
//    }

};


#endif //PARSER_CODE_GEN_GENERATOR_H
