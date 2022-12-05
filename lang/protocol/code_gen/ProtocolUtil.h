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

    static short get_minimum_byte_representation(uint64_t x) {
        uint64_t eraser = 0xFF00000000000000;
        short max_bytes = sizeof(uint64_t);

        if(x == 0) {
            return 1;
        }

        for (int i = 0; i < max_bytes; ++i) {
            if((eraser & x) == 0) {
                eraser >>= 8;
            } else {
                return max_bytes - i;
            }
        }
        throw;
    }

};


#endif //PROTOCOL_CODE_GEN_COMPILER_UTIL_H
