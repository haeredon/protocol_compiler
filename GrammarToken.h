#ifndef GRAMMAR_TOKEN_H
#define GRAMMAR_TOKEN_H

#include "Token.h"
#include "LexerToken.h"

#include<string>
#include<regex>


namespace ProtocolParser {


    // TODO: should use a builder pattern
    class GrammarToken : public Token {

    	private:

            std::regex regex;

            bool term;
            bool has_regex;

    	public:

            GrammarToken() : Token("", "") {}

            explicit GrammarToken(std::string tag, std::string value, bool term);

            explicit GrammarToken(std::string tag, std::string value, bool term, std::regex regex);

            bool is_term();

            bool is_var_term();

            bool is_term_match(LexerToken token);

            bool operator==(const GrammarToken& rhs) const;

            bool operator!=(const GrammarToken& rhs) const;
    };






}

template<> struct std::hash<ProtocolParser::GrammarToken> {
    std::size_t operator()(ProtocolParser::GrammarToken const& token) const noexcept {
        return (hash<std::string>()(token.get_tag()) << 1) ^ hash<std::string>()(token.get_value());
    }
};

#endif /* GRAMMAR_TOKEN_H */