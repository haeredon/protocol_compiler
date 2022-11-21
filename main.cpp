#include "Production.h"
#include "Grammar.h"
#include "ParserAction.h"
#include "Node.h"
#include "lang/protocol/code_gen/ProtocolClass.h"
#include "lang/protocol/code_gen/Generator.h"
#include "lang/protocol/GrammarDefs.h"
#include "lang/protocol/LexerDefs.h"
#include "ParseException.h"
#include "Lexer.h"

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


        Lexer lexer(LexerDefs::REG_TOKEN, ' ');
        Grammar grammar(GrammarDefs::PRODUCTIONS);
        Node* parse_tree;

        try {
            lexer.parse(in);
            std::vector<LexerToken> tokens = lexer.get_tokens();
            tokens.push_back(LexerToken("END", "END", in.size())); // should be a better way of doing this

//            std::cout << grammar.to_string();
            parse_tree = grammar.parse(tokens);
        } catch (ParseException<LexerToken> e) {
            std::cout << e.get_info() << ". At position: " << e.get_lexer_token().get_position() << std::endl;
            std::cout << "Value: " << e.get_lexer_token().get_value() << std::endl;
            std::cout << "Tag: " << e.get_lexer_token().get_tag() << std::endl;
            exit(EXIT_FAILURE);
        }



/******************************************* CODE GENERATION *****************************************************/

        Generator<std::pair<std::string, std::string>> generator;
        std::vector<std::pair<std::string, std::string>> classes = generator.generate(parse_tree);

        std::vector<std::pair<std::string, std::string>>::iterator it;

        for(auto& name_class : classes) {
            std::ofstream out_file;
            out_file.open(out + std::get<0>(name_class) + ".h");

            if (!out_file.good()) {
                std::cout << "Could not open " << optarg;
                exit(EXIT_FAILURE);
            }

            out_file << std::get<1>(name_class);
        }

        return 0;
    }

