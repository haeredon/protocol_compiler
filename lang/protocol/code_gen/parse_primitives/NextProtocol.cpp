//
// Created by skod on 1/1/22.
//

#include "NextProtocol.h"

const std::string &NextProtocol::get_default_next() const {
    return default_next;
}

const std::list<Field*>& NextProtocol::get_priorities() const {
    return priorities;
}

void NextProtocol::set_default_next(const std::string &defaultNext) {
    default_next = defaultNext;
}

void NextProtocol::add_next(Field* field) {
    priorities.push_back(field);
}

NextProtocol::NextProtocol() : default_next("UNKNOWN") {}
