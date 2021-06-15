#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "GrammarToken.h"
#include "ParserAction.h"
#include "Node.h"

#include<map>
#include<string>
#include<utility>
#include<vector>
#include<regex>
#include<stack>
#include<iostream>
#include<regex>
#include<algorithm>


namespace ProtocolParser {

    template<class TOKEN_T, class ACTION_T>
    class Production {

    private:

        TOKEN_T left;
        std::vector<TOKEN_T> right;


        ACTION_T action;
        std::vector<ACTION_T> syncs;


    public:

        Production() {
        }

        Production(const TOKEN_T &left, std::vector<TOKEN_T> &right, ACTION_T action, std::vector<ACTION_T> syncs)
                : left(left),
                  right(right),
                  action(action),
                  syncs(syncs) {
        }

        Production(const TOKEN_T &left, std::vector<TOKEN_T> &&right, ACTION_T action, std::vector<ACTION_T> syncs)
                : left(left),
                  right(right),
                  action(action),
                  syncs(syncs) {
        }

        const TOKEN_T &get_left() {
            return left;
        }

        const std::vector<TOKEN_T> get_right() {
            return right;
        }

        std::string to_string() {
            std::string out_str = left.get_value() + " -> ";

            typename std::vector<TOKEN_T>::iterator it;

            for (it = right.begin(); it != right.end(); ++it) {
                out_str += (*it).get_value() + " ";
            }

            return out_str;
        }

        std::vector<ACTION_T> get_syncs() {
            return syncs;
        }

        ACTION_T get_action() {
            return action;
        }

    };

}

#endif /* PRODUCTION_H */
