#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include "Token.h"




namespace ProtocolParser {

   // enum class Token_type { KEY_WORD, VAR, INT, WILDCARD, COMMA, PAR_START, PAR_END };

    class LexerToken : public Token {

    	private:

        std::size_t position;

    	public:

    	    explicit LexerToken(std::string type, std::string value, std::size_t position);

    	    std::size_t get_position() const {
    	        return position;
    	    }

    };




}

#endif /* LEXER_TOKEN_H */