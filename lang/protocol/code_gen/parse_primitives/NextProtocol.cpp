//
// Created by skod on 1/1/22.
//

#include "NextProtocol.h"

const std::string &NextProtocol::get_default_next() const {
    return default_next;
}

const std::list<std::unique_ptr<Field>>& NextProtocol::get_priorities() const {
    return priorities;
}

void NextProtocol::set_default_next(const std::string &defaultNext) {
    default_next = defaultNext;
}

void NextProtocol::add_next(std::unique_ptr<Field> field) {
    priorities.push_back(std::move(field));
}

NextProtocol::NextProtocol() {}
