//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_CLASS_H
#define PROTOCOL_COMPILER_CLASS_H

#include "Field.h"
#include "While.h"
#include "NextProtocol.h"
#include "Statement.h"

#include <list>
#include "unordered_map"

class Class {

    std::list<Statement*> statements;

    std::unordered_map<std::string, Field*> name_to_field;

    NextProtocol next_protocol;

    std::string name;

public:
    void set_name(std::string name);

    void add_statement(Statement* stmt);

    bool has_variable(std::string name);

    void add_variable(std::string name, Field* stmt);

    Field* get_variable(std::string name);

    void set_next_protocol(NextProtocol&& nextProtocol);

    std::list<Statement*> &get_statements();

    const NextProtocol &get_next_protocol() const;

    const std::string &get_name() const;
};


#endif //PROTOCOL_COMPILER_CLASS_H
