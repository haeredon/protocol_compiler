//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_CLASS_H
#define PROTOCOL_COMPILER_CLASS_H

#include "Field.h"
#include "FieldGroup.h"
#include "Property.h"

class Class {

    std::vector<Field> fields;

    std::vector<FieldGroup> field_groups;

    std::vector<Property> properties;

    std::string name;

public:
    void set_name(std::string name);

    void add_field(Field field);

    void add_field_group(FieldGroup group);

    void add_property(Property property);

    bool has_field(const std::string& field_name) ;

    Field& get_field(const std::string& field_name);
};


#endif //PROTOCOL_COMPILER_CLASS_H
