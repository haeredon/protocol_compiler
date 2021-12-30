//
// Created by skod on 12/7/21.
//

#include "Bitmap.h"

void Bitmap::append_mapping(std::string name, std::tuple<std::size_t, std::size_t> mapping) {
    name_to_map[name] = mapping;
}

const std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> &Bitmap::get_name_to_map() const {
    return name_to_map;
}
