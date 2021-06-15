#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Token.h"
#include "Production.h"
#include "LexerToken.h"
#include "Node.h"

#include<map>
#include<string>
#include<utility>
#include<vector>
#include<regex>
#include<unordered_map>
#include<set>
#include<iostream>
#include<sstream>


namespace ProtocolParser {

    template<class PRODUCTION_T, class NODE_T = Node>
    class Grammar {

    private:

        std::vector<PRODUCTION_T> productions;

        std::unordered_map<GrammarToken, std::set<GrammarToken>> symbol_to_first;
        std::unordered_map<GrammarToken, std::set<GrammarToken>> symbol_to_follow;

        std::unordered_map<GrammarToken, std::unordered_map<std::string, PRODUCTION_T>> parser_matrix;

        GrammarToken start_sym;



        bool has_first_epsilon(const GrammarToken& symbol) {
            return symbol_to_first[symbol].count(Grammar::EPSILON) > 0;
        }

        template<class InputIterator>
        std::size_t add_follows(GrammarToken &to_token, InputIterator first, InputIterator last) {
            std::size_t num_added = 0;

            for (; first != last; ++first) {
                GrammarToken to_add = *first;

                if (to_add != Grammar::EPSILON) {
                    num_added += symbol_to_follow[to_token].insert(to_add).second ? 1 : 0;
                }
            }

            return num_added;
        }

        void create_follows() {
            std::size_t num_added = -1;

            while(num_added != 0) {
                num_added = 0;
                typename std::vector<PRODUCTION_T>::iterator it;

                for(it = productions.begin(); it != productions.end(); ++it) {
                    Production production = *it;

                    std::vector<GrammarToken> right = production.get_right();
                    GrammarToken left = production.get_left();

                    std::vector<GrammarToken>::reverse_iterator right_it;
                    std::set<GrammarToken> firsts_added;

                    if(left == Grammar::START) {
                        symbol_to_follow[left].insert(Grammar::END);
                    }

                    if(right.size() == 1 && !right.front().is_term()) {
                        add_follows(right.front(), symbol_to_follow[left].begin(), symbol_to_follow[left].end());
                    } else {
                        bool epsilon_end = true;

                        for(right_it = right.rbegin(); right_it != right.rend() - 1; ++right_it) {
                            GrammarToken token = *right_it;
                            GrammarToken pre_token = *(right_it + 1);

                            if((token.is_term() || !has_first_epsilon(token)) && right_it != right.rbegin()) {
                                epsilon_end = false;
                            }

                            if(epsilon_end) {
                                if(!token.is_term()) {
                                    num_added += add_follows(token, symbol_to_follow[left].begin(), symbol_to_follow[left].end());
                                }

                                if(!pre_token.is_term()) {
                                    num_added += add_follows(pre_token, symbol_to_follow[left].begin(), symbol_to_follow[left].end());
                                }
                            }

                            if(!pre_token.is_term()) {
                                firsts_added.insert(symbol_to_first[token].begin(), symbol_to_first[token].end());
                                num_added += add_follows(pre_token, firsts_added.begin(), firsts_added.end());
                            }
                        }
                    }


                }
            }
        }

        void create_firsts() {
            bool added_new = true;
            while(added_new) {

                added_new = false;
                typename std::vector<PRODUCTION_T>::iterator it;

                for(it = productions.begin(); it != productions.end(); ++it) {
                    Production production = *it;

                    std::vector<GrammarToken> right = production.get_right();
                    GrammarToken left = production.get_left();
                    std::size_t num_firsts = symbol_to_first[left].size();

                    std::vector<GrammarToken>::iterator right_it;
                    bool only_add_term = false;

                    for(right_it = right.begin(); right_it != right.end(); ++right_it) {
                        GrammarToken token = *right_it;

                        if(only_add_term) {
                            if(token.is_term()) {
                                symbol_to_first[token].insert(token);
                            }
                        } else {
                            if(!token.is_term() && !has_first_epsilon(token)) {
                                symbol_to_first[left].insert(symbol_to_first[token].begin(), symbol_to_first[token].end());
                                only_add_term = true;
                            }

                            if(token.is_term()) {
                                symbol_to_first[left].insert(token);
                                symbol_to_first[token].insert(token);
                                only_add_term = true;
                            }

                            if(!token.is_term() && has_first_epsilon(token)) {
                                symbol_to_first[left].insert(symbol_to_first[token].begin(), symbol_to_first[token].end());
                                if(right_it + 1 == right.end()) {
                                    symbol_to_first[left].insert(Grammar::EPSILON);
                                };
                            }
                        }
                    }

                    if(num_firsts != symbol_to_first[left].size()) {
                        added_new = true;
                    }
                }
            }
        }

        void create_parsing_table() {

            typename std::vector<PRODUCTION_T>::iterator it;

            for(it = productions.begin(); it != productions.end(); ++it) {
                Production production = *it;

                GrammarToken right = production.get_right().front();
                GrammarToken left = production.get_left();
                std::set<GrammarToken> right_firsts = symbol_to_first[right];

                std::set<GrammarToken>::iterator right_it;
                for(right_it = right_firsts.begin(); right_it != right_firsts.end(); ++right_it) {
                    GrammarToken token = *right_it;

                    if(token != Grammar::EPSILON) {
                        parser_matrix[left][token.get_value()] = production;
                    }

                    if(has_first_epsilon(token)) {
                        std::set<GrammarToken>::iterator f_it;
                        std::set<GrammarToken> left_follows = symbol_to_follow[left];

                        for(f_it = left_follows.begin(); f_it != left_follows.end(); ++f_it) {
                            GrammarToken follow_token = *f_it;
                            parser_matrix[left][follow_token.get_value()] = production;
                        }
                    }
                }
            }
         }


    public:

        Grammar(std::vector<PRODUCTION_T> &productions) : productions(productions) {
            typename std::vector<PRODUCTION_T>::iterator it;

            for(it = productions.begin(); it != productions.end(); ++it) {
                GrammarToken left = it->get_left();

                if(left == Grammar::START) {
                    start_sym = left;
                }
            }

            create_firsts();
            create_follows();
            create_parsing_table();
        }

        NODE_T parse(const std::vector<LexerToken> &tokens) {
            std::vector<LexerToken>::const_iterator token_it = tokens.begin();
            auto x = ParserAction<Node*>(start_sym);
            std::string last_val;

            std::deque<ParserAction<Node*>> stack;

            stack.push_front(ParserAction<Node*>(Grammar::END));
            stack.push_front(x);

            while (x.get_grammar_token() != Grammar::END) {
                std::string tag = (*token_it).get_tag();
                std::string value = (*token_it).get_value();
                LexerToken lexer_token = (*token_it);
                GrammarToken grammar_token = x.get_grammar_token();

                if(x.is_action()) {
                    x.execute(stack);
                    stack.pop_front();
                } else if (grammar_token.is_term_match(lexer_token)) {
                    ++token_it;
                    stack.pop_front();
                    stack.front().add_value(new Node(nullptr, value));
                } else if (grammar_token.is_term()) {
                    std::cout << "ERRRORR_1!!" << std::endl;
                    throw "ERRRORR_1!!";
                } else {
                    bool entry_exists = parser_matrix[grammar_token].contains(tag);

                    if (entry_exists) {
                        PRODUCTION_T production = parser_matrix[grammar_token][tag];

                        std::vector<GrammarToken> right = production.get_right();
                        GrammarToken left = production.get_left();

                        ParserAction<Node*> action(production.get_action(), x.get_inherits());

                        stack.pop_front();

                        for (int i = right.size() - 1; i >= 0; i--) {
                            auto symbol = ParserAction<Node*>(right[i]);
                            auto sync = ParserAction<Node*>(production.get_syncs()[i]);

                            if (symbol.get_grammar_token() != Grammar::EPSILON) {
                                stack.push_front(sync);
                                stack.push_front(symbol);
                            } else {
                                stack.push_front(sync);
                            }
                        }

                        stack.push_front(action);
                    } else {
                        std::cout << "ERRRORR_2!!" << std::endl;
                        throw "ERRRORR_2!!";
                    }
                }

                x = stack.front();
            }

            return *(stack.front().get_values().front());
        }

        std::string to_string() {
            std::stringstream ss;
            ss << "Firsts" << std::endl << std::endl;

            std::unordered_map<GrammarToken, std::set<GrammarToken>>::iterator o_it;
            std::set<GrammarToken>::iterator i_it;

            for(o_it = symbol_to_first.begin(); o_it != symbol_to_first.end(); ++o_it) {
                GrammarToken non_term = o_it->first;
                std::set<GrammarToken> firsts = o_it->second;

                ss << "non_term: " << non_term.get_value() << std::endl;


                for(i_it = firsts.begin(); i_it != firsts.end(); ++i_it) {
                    ss << "f: " << (*i_it).get_value() << std::endl;
                }

                std::cout << std::endl;
            }

            ss << "Follows" << std::endl << std::endl;

            for(o_it = symbol_to_follow.begin(); o_it != symbol_to_follow.end(); ++o_it) {
                GrammarToken non_term = o_it->first;
                std::set<GrammarToken> firsts = o_it->second;

                ss << "non_term: " << non_term.get_value() << std::endl;

                for(i_it = firsts.begin(); i_it != firsts.end(); ++i_it) {
                    ss << "f: " << (*i_it).get_value() << std::endl;
                }

                std::cout << std::endl;
            }

            ss << "Parser Table" << std::endl << std::endl;

            typename std::unordered_map<GrammarToken, std::unordered_map<std::string, PRODUCTION_T>>::iterator p_it;
            typename std::unordered_map<std::string, PRODUCTION_T>::iterator m_it;

            for(p_it = parser_matrix.begin(); p_it != parser_matrix.end(); ++p_it) {
                GrammarToken non_term = p_it->first;
                std::unordered_map<std::string, PRODUCTION_T> term_map = p_it->second;

                ss << "non_term: " << non_term.get_value() << std::endl;

                for(m_it = term_map.begin(); m_it != term_map.end(); ++m_it) {
                    ss << "term: " << m_it->first << " maps to: " << m_it->second.to_string() << std::endl;
                }

                std::cout << std::endl;
            }

            return ss.str();
        }

        static const GrammarToken START;
        static const GrammarToken END;
        static const GrammarToken EPSILON;
    };

    template<class PRODUCTION_T, class NODE_T>
    const GrammarToken Grammar<PRODUCTION_T, NODE_T>::START = GrammarToken("START", "START", false);

    template<class PRODUCTION_T, class NODE_T>
    const GrammarToken Grammar<PRODUCTION_T, NODE_T>::END = GrammarToken("END", "END", false);

    template<class PRODUCTION_T, class NODE_T>
    const GrammarToken Grammar<PRODUCTION_T, NODE_T>::EPSILON = GrammarToken("EPSILON", "EPSILON", true);

}

#endif /* GRAMMAR_H */
