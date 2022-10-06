//
// Created by skod on 10/5/22.
//

#ifndef PROTOCOL_COMPILER_UTIL_H
#define PROTOCOL_COMPILER_UTIL_H

#include <cctype>
#include <string>

namespace ProtocolParser {

    class Util {

    private:

        Util();

    public:

        static std::string to_upper(const std::string& str);

        Util(const Util &) = delete;

        Util &operator=(const Util &) = delete;

    };

}

#endif //PROTOCOL_COMPILER_UTIL_H
