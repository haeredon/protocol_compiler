cmake_minimum_required(VERSION 3.17)

project(protocol_compiler)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)


add_executable(parser
        lang/protocol/code_gen/BaseClass.h
        lang/protocol/code_gen/ProtocolClass.h
        lang/protocol/code_gen/Generator.h
        lang/protocol/code_gen/Field.h
        lang/protocol/Tokens.h
        lang/protocol/LexerDefs.h
        lang/protocol/GrammarDefs.h
        CodeGen.h
        ParserAction.h
        GrammarToken.cpp
        Grammar.h
        Lexer.cpp
        LexerToken.cpp
        main.cpp
        Production.h
        Token.cpp
        Node.h lang/protocol/code_gen/BuildClass.h lang/protocol/code_gen/ProtocolBaseClass.h ParseException.h lang/protocol/code_gen/Conditional.h lang/protocol/code_gen/FieldGroup.h)
