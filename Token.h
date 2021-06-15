#ifndef TOKEN_H
#define TOKEN_H


#include<string>



namespace ProtocolParser {

   
    class Token {

    	protected:

            std::string tag;
    	    std::string value;


    	public:

    		explicit Token(std::string type, std::string value);

            std::string get_tag() const;

    		std::string get_value() const;

    		bool operator==(const Token &other) const;

    		bool operator<(const Token &other) const;

    };




}

#endif /* TOKEN_H */