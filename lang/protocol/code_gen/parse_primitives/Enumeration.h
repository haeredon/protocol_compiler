//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_ENUMERATION_H
#define PROTOCOL_COMPILER_ENUMERATION_H

#include <unordered_map>
#include <string>

class Enumeration {

    std::unordered_map<std::string, std::size_t> enum_to_val;

public:
    void add_val(std::string name, std::size_t val);

    const std::unordered_map<std::string, std::size_t> &get_enum_to_Val() const;

};


#endif //PROTOCOL_COMPILER_ENUMERATION_H
