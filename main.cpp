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

        std::string in;
        std::string out;

        for(;;)
        {
            switch(getopt(argc, argv, "i:o:h"))
            {
                case 'i': {
                    std::ifstream in_file;
                    in_file.open(optarg);

                    if (!in_file.good()) {
                        std::cout << "Could not open " << optarg;
                        exit(EXIT_FAILURE);
                    }

                    std::stringstream ss;
                    ss << in_file.rdbuf();
                    in = ss.str();
                    continue;
                }
                case 'o':
                    out = optarg;
                    continue;
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

        if(in.empty()) {
            printf("No input file given\n");
        }

        if(out.empty()) {
            out = "./";
        }


        using namespace ProtocolParser;

/**************************************** LEXER ********************************************************/

        Lexer lexer(LexerDefs::REG_TOKEN, ' ');

        lexer.parse(in);

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

            std::ofstream out_file;
            out_file.open(out + (*it)->get_name() + ".h");

            if (!out_file.good()) {
                std::cout << "Could not open " << optarg;
                exit(EXIT_FAILURE);
            }

            out_file << (*it)->to_string();
        }

        return 0;
    }

