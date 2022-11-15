//
// Created by skod on 11/14/22.
//

#ifndef PROTOCOL_CODE_GEN_COMPILER_UTIL_H
#define PROTOCOL_CODE_GEN_COMPILER_UTIL_H

#include <string>

class ProtocolUtil {


public:

    static std::string length_to_type(short length) {
        switch (length) {
            case 1:
                return "uint8_t";
            case 2:
                return "uint16_t";
            case 4:
                return "uint32_t";
            case 8:
                return "uint64_t";
            default:
                throw "length: " + std::to_string(length) + " does not convert to a type";
        }
    }


};


#endif //PROTOCOL_CODE_GEN_COMPILER_UTIL_H
