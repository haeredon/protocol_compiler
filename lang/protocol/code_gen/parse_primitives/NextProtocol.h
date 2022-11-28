//
// Created by skod on 1/1/22.
//

#ifndef PROTOCOL_COMPILER_NEXTPROTOCOL_H
#define PROTOCOL_COMPILER_NEXTPROTOCOL_H


#include <string>
#include <list>
#include <memory>
#include <vector>
#include "Expression.h"
#include "Field.h"

class NextProtocol {

private:

    std::string default_next;

    std::list<Field*> priorities;

public:

    NextProtocol();

    const std::string &get_default_next() const;

    const std::list<Field*>& get_priorities() const;

    void set_default_next(const std::string &defaultNext);

    void add_next(Field* field);

    NextProtocol(const NextProtocol& other) = delete;
    NextProtocol& operator=(const NextProtocol& other) = delete;

    NextProtocol(NextProtocol&& other) {
        default_next = other.default_next;
        priorities = std::move(other.priorities);
    }

    NextProtocol& operator=(NextProtocol&& other) {
        default_next = other.default_next;
        priorities = std::move(other.priorities);
        return *this;
    };

};


#endif //PROTOCOL_COMPILER_NEXTPROTOCOL_H
