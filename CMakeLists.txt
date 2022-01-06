cmake_minimum_required(VERSION 3.17)

project(protocol_compiler)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)


add_executable(parser
        lang/protocol/code_gen/ProtocolClass.h
        lang/protocol/code_gen/Generator.h
        lang/protocol/Tokens.h
        lang/protocol/LexerDefs.h
        lang/protocol/GrammarDefs.h
        lang/protocol/Tokens.cpp
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
        lang/protocol/code_gen/parse_primitives/PrimitiveExpr.cpp
        lang/protocol/code_gen/parse_primitives/PrimitiveExpr.h
        lang/protocol/code_gen/parse_primitives/FunctionExpr.cpp
        lang/protocol/code_gen/parse_primitives/FunctionExpr.h
        lang/protocol/code_gen/parse_primitives/DotExpression.cpp
        lang/protocol/code_gen/parse_primitives/DotExpression.h
        lang/protocol/code_gen/parse_primitives/OperatorExpr.cpp
        lang/protocol/code_gen/parse_primitives/OperatorExpr.h
        lang/protocol/code_gen/ProtocolClass.cpp
        lang/protocol/code_gen/parse_primitives/ExpressionHandler.h
        lang/protocol/code_gen/parse_primitives/FieldExpr.cpp
        lang/protocol/code_gen/parse_primitives/FieldExpr.h
        lang/protocol/code_gen/parse_primitives/NextProtocol.cpp
        lang/protocol/code_gen/parse_primitives/NextProtocol.h lang/protocol/code_gen/BuildClass.cpp lang/protocol/code_gen/BuildClass.h)
