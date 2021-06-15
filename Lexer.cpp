#include "Lexer.h"

#include<iostream>
#include<regex>
#include<algorithm>

namespace ProtocolParser {


    Lexer::Lexer(std::vector<std::pair<std::regex, std::string>> reg_type, char delimiter) : reg_type(reg_type), delimiter(delimiter) {

    }

    void Lexer::trim_token_text(std::string &token_str) {
        token_str.erase(token_str.begin(), std::find_if(token_str.begin(), token_str.end(), [](unsigned char ch) {
          return !std::isspace(ch);
        }));
    }

    void Lexer::parse(std::string text) {
        std::string token_str = text;
        while(token_str.size() != 0) {
            std::smatch matcher;
            int num_char_tokenized = 0;
            bool match_found = false;

            for (std::vector<std::pair<std::regex, std::string>>::iterator it=reg_type.begin(); it != reg_type.end(); ++it) {
                std::regex_search (token_str, matcher, it->first);

                // a match was found and it start at index 0 in the text
                if(matcher.size() != 0 && matcher.position(0) == 0) {
                    tokens.push_back(LexerToken(it->second, token_str.substr(0, matcher.length(0))));
                    num_char_tokenized = matcher.length(0);
                    match_found = true;
                    break;
                }
            }

            if(!match_found) {
                throw "Lexer error!";
            }

            token_str = token_str.substr(num_char_tokenized);
            trim_token_text(token_str);
        }

    }

    void parse(std::ifstream in) {


    }

    std::vector<LexerToken> Lexer::get_tokens() {
        return tokens;
    }










}