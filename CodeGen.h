//
// Created by skod on 11/05/2021.
//

#include "Node.h"

#ifndef PARSER_CODEGEN_H
#define PARSER_CODEGEN_H

namespace ProtocolParser {

    template<class RET_T>
    class CodeGen {

    public:

        virtual std::vector<RET_T> generate(Node* ast) = 0;

    };

}

#endif //PARSER_CODEGEN_H




/*


Class class;

void generate(node) {
    if(node.val is protocol)
    gen_base(base_class, node)

    return list(base_class, builder_class)
}

void gen_class(class, node) {
    class.name = node.val

    foreach(child in children) {
        gen_class_attr(class, child);
    }
}

*/
