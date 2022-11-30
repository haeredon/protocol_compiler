//
// Created by skod on 12/7/21.
//

#include "Class.h"
#include "../ClassVisitor.h"

#include <algorithm>

void Class::set_name(std::string name) {
    this->name = name;
}

void Class::add_statement(Statement *stmt) {
    statements.push_back(stmt);
}

const std::list<Statement*> &Class::get_statements() const {
    return statements;
}

const std::string &Class::get_name() const {
    return name;
}

const NextProtocol &Class::get_next_protocol() const {
    return next_protocol;
}

void Class::set_next_protocol(NextProtocol&& nextProtocol) {
    next_protocol = std::move(nextProtocol);
}

bool Class::has_variable(std::string name) {
    return name_to_field.contains(name);
}

Field* Class::get_variable(std::string name) {
    return name_to_field.at(name);
}

void Class::add_variable(std::string name, Field* stmt) {
    name_to_field.emplace(name, stmt);
}

void Class::visit(ClassVisitor *visitor) const {
    visitor->visit(*this);
}
