//
// Created by skod on 10/5/22.
//

#include "Util.h"

#include <cctype>

namespace ProtocolParser {

    Util::Util() {}

    std::string Util::to_upper(const std::string& str) {
        std::string new_str;

        for(const char& ch : str) {
            char upper = (char) toupper(ch);
            new_str.append(&upper, 1);
        }

        return new_str;
    }

}