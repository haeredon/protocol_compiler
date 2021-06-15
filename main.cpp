#include "Lexer.h"
#include "Production.h"
#include "Grammar.h"
#include "ParserAction.h"
#include "Node.h"
#include "lang/protocol/code_gen/ParseClass.h"
#include "lang/protocol/code_gen/Generator.h"
#include "lang/protocol/GrammarDefs.h"
#include "lang/protocol/LexerDefs.h"

#include<string>
#include<vector>
#include<iostream>
#include<unistd.h>
#include<cstdlib>



    int main(int argc, char *argv[]) {

        std::string code;

        for(;;)
        {
            switch(getopt(argc, argv, "f:h"))
            {
                case 'f': {
                    std::ifstream inFile;
                    inFile.open(optarg);

                    if (!inFile.good()) {
                        std::cout << "Could not open " << optarg;
                        exit(EXIT_FAILURE);
                    }

                    std::stringstream ss;
                    ss << inFile.rdbuf();
                    code = ss.str();
                    continue;
                }
                case '?':
                case 'h':
                default :
                    printf("Help/Usage Example\n");
                    exit(EXIT_SUCCESS);
                case -1:
                    break;
            }

            break;
        }


        using namespace ProtocolParser;

/**************************************** LEXER ********************************************************/

        Lexer lexer(LexerDefs::REG_TOKEN, ' ');

        lexer.parse(code);

        std::vector<LexerToken> tokens = lexer.get_tokens();
        tokens.push_back(LexerToken("END", "END")); // should be a better way of doing this

/******************************************* GRAMMER STUFF *****************************************************/

        Grammar grammar(GrammarDefs::PRODUCTIONS);
        Node parse_tree = grammar.parse(tokens);

/******************************************* CODE GENERATION *****************************************************/

        Generator<BaseClass, ParseClass> generator;
        std::vector<BaseClass*> classes = generator.generate(parse_tree);

        std::vector<BaseClass*>::iterator it;

        for(it = classes.begin() ; it != classes.end() ; ++it) {
            std::cout << std::endl << std::endl << (*it)->to_string() << std::endl;
        }

        return 0;
    }

