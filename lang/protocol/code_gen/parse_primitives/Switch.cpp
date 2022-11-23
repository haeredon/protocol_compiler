//
// Created by skod on 11/23/22.
//

#include "Switch.h"


Switch::Switch(Expression* compare_value, std::list<Case>&& cases) :
compare_value(compare_value), cases(std::move(cases)) {}

const Expression* Switch::get_compare_value() const {
    return compare_value;
}

const std::list<Case>& Switch::get_cases() const {
    return cases;
}