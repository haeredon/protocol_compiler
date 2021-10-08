//
// Created by skod on 11/05/2021.
//

#ifndef PARSER_CODE_GEN_GENERATOR_H
#define PARSER_CODE_GEN_GENERATOR_H

#include "CodeGen.h"
#include "BaseClass.h"
#include "Field.h"
#include "BuildClass.h"

#include <vector>
#include <iostream>

template<class RET_T, class PARSE_T>
class Generator : public ProtocolParser::CodeGen<RET_T*> {

public:

    std::vector<RET_T*> generate(ProtocolParser::Node* ast) {
        std::vector<RET_T*> classes;
        std::vector<ProtocolParser::Node*>::iterator it;

        for(it = ast->get_children().begin() ; it != ast->get_children().end() ; ++it) {
            classes.push_back(gen_class(*it));
        }

        return classes;
    }

    RET_T* gen_class(ProtocolParser::Node* ast) {
        BuildClass* buildClass = new BuildClass("Builder");
        PARSE_T* new_class = new PARSE_T(buildClass);

        std::vector<ProtocolParser::Node*>::iterator it;

        for(it = ast->get_children().begin() ; it != ast->get_children().end() ; ++it) {
            ProtocolParser::Node* class_attr = *it;

            if(class_attr->get_value() == "NAME") {
                add_name(class_attr, *new_class);
                buildClass->set_to_build_name(new_class->get_name());
            } else if(class_attr->get_value() == "ATTRIBUTES") {
                add_attributes(class_attr, *buildClass);
                add_attributes(class_attr, *new_class);
            }
        }

        return new_class;
    }

    void add_name(ProtocolParser::Node* ast, PARSE_T& new_class) {
        new_class.add_name(ast->get_children().front()->get_value());
    }

    void add_attributes(ProtocolParser::Node* ast, BaseClass& new_class) {
        std::vector<ProtocolParser::Node*> children = ast->get_children();
        std::vector<ProtocolParser::Node*>::iterator it;

        for(it = ast->get_children().begin() ; it != ast->get_children().end() ; ++it) {
            ProtocolParser::Node* attr = *it;

            if(attr->get_value() == "ATTR") {
                add_field(attr, new_class);
            }
        }

    }

    void add_field(ProtocolParser::Node* ast, BaseClass& new_class) {
        std::vector<ProtocolParser::Node*> children = ast->get_children();

        std::vector<ProtocolParser::Node*>::iterator it;

        std::string name;
        std::string length;
        std::unordered_map<std::string, std::size_t> enumeration;
        std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> bitmap;

        bool is_inner = false;
        std::size_t inner_priority = 0;

        std::string conditional_name;
        std::vector<std::string> cond_args;

        for(it = ast->get_children().begin() ; it != ast->get_children().end() ; ++it) {
            ProtocolParser::Node* attr = *it;

            if(attr->get_value() == "NAME") {
                name = attr->get_children().front()->get_value();
            } else if(attr->get_value() == "LENGTH") {
                length = attr->get_children().front()->get_value();
            } else if(attr->get_value() == "CONDITIONAL") {
                std::vector<ProtocolParser::Node*> children = attr->get_children();

                conditional_name = children.front()->get_children().front()->get_value();

                std::vector<ProtocolParser::Node*>::iterator c_it;
                std::vector<ProtocolParser::Node*> args = children.back()->get_children();

                for(c_it = args.begin() ; c_it != args.end() ; ++c_it) {
                    cond_args.push_back((*c_it)->get_value());
                }
            } else if(attr->get_value() == "MAP") {
                std::vector<ProtocolParser::Node*>::iterator t_it;

                std::size_t num_taken = 0;
                for(t_it = attr->get_children().begin() ; t_it != attr->get_children().end() ; ++t_it) {
                    std::string name = (*t_it)->get_children().front()->get_children().front()->get_value();
                    std::size_t value = stoi((*t_it)->get_children().back()->get_children().front()->get_value());

                    bitmap[name] = std::tuple(num_taken, num_taken + value - 1);
                    num_taken += value;
                }
            } else if(attr->get_value() == "ENUM") {
                std::vector<ProtocolParser::Node*>::iterator t_it;

                for(t_it = attr->get_children().begin() ; t_it != attr->get_children().end() ; ++t_it) {
                    std::string name = (*t_it)->get_children().front()->get_children().front()->get_value();
                    std::size_t value = stoi((*t_it)->get_children().back()->get_children().front()->get_value());

                    enumeration[name] = value;
                }
            } else if(attr->get_value() == "INNER") {
                is_inner = true;
                inner_priority = std::stol(attr->get_children().front()->get_children().front()->get_value());
            }
        }

        Field field(name, length, enumeration, bitmap);
        field.set_conditional(conditional_name, cond_args);
        field.get_inner().is_inner = is_inner;
        field.get_inner().priority = inner_priority;
        new_class.add_field(std::move(field));
    }



};


#endif //PARSER_CODE_GEN_GENERATOR_H
