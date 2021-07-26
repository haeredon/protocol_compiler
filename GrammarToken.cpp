#include "GrammarToken.h"
#include "LexerToken.h"

namespace ProtocolParser {

    GrammarToken::GrammarToken(std::string tag, std::string value, bool term) : Token(tag, value), term(term) {
        has_regex = false;
    }

    GrammarToken::GrammarToken(std::string tag, std::string value, bool term, std::regex regex) : Token(tag, value), term(term), regex(regex) {
        has_regex = true;
    }

    bool GrammarToken::is_term() {
        return term;
    }

    bool GrammarToken::is_var_term() {
        return is_term() && has_regex;
    }

    bool GrammarToken::is_term_match(LexerToken token) {
        if(is_var_term()) {
            std::regex reg = regex;
            std::smatch str_match;

            std::string val = token.get_value();
            return std::regex_match(val, str_match, reg);
        } else if(is_term()) {
            return token.get_tag() == get_value();
        }

        return false;
    }

    bool GrammarToken::operator==(const GrammarToken& rhs) const {
        return rhs.get_tag() == get_tag() && rhs.get_value() == get_value();
    }

    bool GrammarToken::operator!=(const GrammarToken& rhs) const {
        return !(*this == rhs);
    }
}