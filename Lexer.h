#ifndef LEXER_H
#define LEXER_H

#include "LexerToken.h"

#include<map>
#include<string>
#include<utility>
#include<vector>
#include<regex>
#include<fstream>


namespace ProtocolParser {

    class Lexer {

    	private:

    		char delimiter;

    		std::vector<LexerToken> tokens;

    		std::vector<std::pair<std::regex, std::string>> reg_type;

    		void trim_token_text(std::string &token_str);

    	public:

    		Lexer(std::vector<std::pair<std::regex, std::string>>, char);

    		void parse(std::string text);

            void parse(std::ifstream in);

    		std::vector<LexerToken> get_tokens();

    };




}

#endif /* LEXER_H */
