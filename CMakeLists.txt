cmake_minimum_required(VERSION 3.17)

project(protocol_compiler)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)


add_executable(parser
        lang/protocol/code_gen/BaseClass.h
        lang/protocol/code_gen/ProtocolClass.h
        lang/protocol/code_gen/Generator.h
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
        Node.h
        lang/protocol/code_gen/BuildClass.h
        lang/protocol/code_gen/ProtocolBaseClass.h
        ParseException.h
        lang/protocol/code_gen/parse_primitives/Bitmap.cpp
        lang/protocol/code_gen/parse_primitives/Bitmap.h
        lang/protocol/code_gen/parse_primitives/Field.cpp
        lang/protocol/code_gen/parse_primitives/Field.h
        lang/protocol/code_gen/parse_primitives/FieldGroup.cpp
        lang/protocol/code_gen/parse_primitives/FieldGroup.h
        lang/protocol/code_gen/parse_primitives/Expression.cpp
        lang/protocol/code_gen/parse_primitives/Expression.h
        lang/protocol/code_gen/parse_primitives/Enumeration.cpp
        lang/protocol/code_gen/parse_primitives/Enumeration.h
        lang/protocol/code_gen/parse_primitives/Class.cpp
        lang/protocol/code_gen/parse_primitives/Class.h
        lang/protocol/code_gen/parse_primitives/Property.cpp
        lang/protocol/code_gen/parse_primitives/Property.h
        lang/protocol/code_gen/parse_primitives/ExprElement.cpp
        lang/protocol/code_gen/parse_primitives/ExprElement.h
        lang/protocol/code_gen/parse_primitives/Primitive.cpp
        lang/protocol/code_gen/parse_primitives/Primitive.h
        lang/protocol/code_gen/parse_primitives/Function.cpp
        lang/protocol/code_gen/parse_primitives/Function.h
        lang/protocol/code_gen/parse_primitives/DotExpression.cpp
        lang/protocol/code_gen/parse_primitives/DotExpression.h
        lang/protocol/code_gen/parse_primitives/Operator.cpp lang/protocol/code_gen/parse_primitives/Operator.h lang/protocol/code_gen/ProtocolClass.cpp)
