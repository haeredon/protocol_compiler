//
// Created by skod on 12/7/21.
//

#ifndef PROTOCOL_COMPILER_BITMAP_H
#define PROTOCOL_COMPILER_BITMAP_H

#include <string>
#include <unordered_map>

class Bitmap {

    std::unordered_map<std::string, std::tuple<std::size_t, std::size_t>> name_to_map;

public:

    void append_mapping(std::string name, std::tuple<std::size_t, std::size_t> mapping);

};


#endif //PROTOCOL_COMPILER_BITMAP_H
