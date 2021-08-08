//
// Created by skod on 09/04/2021.
//

#ifndef PARSER_NODE_H
#define PARSER_NODE_H


#include <vector>
#include <string>

namespace ProtocolParser {

    class Node {

    private:

        Node *parent;

        std::vector<Node *> children;

        std::string val; // TEMP FOR TESTS

    public:

        Node(const Node &other) {
            parent = other.parent;
            children = other.children;
            val = other.val;
        }

        // TEMP FOR TESTS
        Node(Node *parent, std::string val) : parent(parent), val(val) {

        };

        void add_child(Node *child) {
            children.push_back(child);
        }

        std::vector<Node *> &get_children() {
            return children;
        }

        std::string &get_value() {
            return val;
        }

        ~Node() {
            for(auto child : children) {
                delete child;
            }
        }



    };

}

#endif //PARSER_NODE_H
