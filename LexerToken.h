#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include "Token.h"




namespace ProtocolParser {

   // enum class Token_type { KEY_WORD, VAR, INT, WILDCARD, COMMA, PAR_START, PAR_END };

    class LexerToken : public Token {

    	private:

    	public:

    	    explicit LexerToken(std::string type, std::string value);

    };




}

#endif /* LEXER_TOKEN_H */