#ifndef PARSER_ACTION_H
#define PARSER_ACTION_H

#include "Token.h"
#include "GrammarToken.h"

#include<string>
#include<regex>


namespace ProtocolParser {

    // TODO: maybe use inheritence to seperate actions from nonterminals
    template<class NODE_T>
    class ParserAction {

    private:

        GrammarToken token;

        bool no_token;

        void (*action)(std::deque<ParserAction<NODE_T>>&);

        std::vector<NODE_T> inherits;

        std::vector<NODE_T> values;

    public:

        ParserAction(GrammarToken token) : token(token) {
            no_token = false;
        }

        ParserAction(void (*action)(std::deque<ParserAction<NODE_T>>&), std::vector<NODE_T> inherits) : action(action), inherits(inherits) {
            no_token = true;
        }

        ParserAction(void (*action)(std::deque<ParserAction<NODE_T>>&)) : action(action) {
            no_token = true;
        }

        virtual void execute(std::deque<ParserAction<NODE_T>>& stack) {
            action(stack);
        };

        virtual void add_inherit(NODE_T inherit) {
            inherits.push_back(inherit);
        };

        virtual void add_inherits(std::vector<NODE_T> to_insert) {
            inherits.insert(inherits.end(), to_insert.begin(), to_insert.end());
        };

        virtual void add_values(std::vector<NODE_T> to_insert) {
            values.insert(values.end(), to_insert.begin(), to_insert.end());
        };

        virtual void add_value(NODE_T value) {
            values.push_back(value);
        };

        virtual GrammarToken get_grammar_token() {
            return token;
        };

        virtual bool is_action() {
            return no_token;
        };

        virtual std::vector<NODE_T> get_inherits() {
            return inherits;
        };

        virtual std::vector<NODE_T> get_values() {
            return values;
        };


    };


}

#endif /* PARSER_ACTION_H */