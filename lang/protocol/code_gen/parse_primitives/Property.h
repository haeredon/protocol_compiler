//
// Created by skod on 12/10/21.
//

#ifndef PROTOCOL_COMPILER_PROPERTY_H
#define PROTOCOL_COMPILER_PROPERTY_H

#include <string>
#include <vector>

class Property {

    std::string name;

    std::vector<std::string> args;

public:
    void set_name(std::string name);

    void add_arg(std::string& arg);
};


#endif //PROTOCOL_COMPILER_PROPERTY_H
