cmake_minimum_required(VERSION 3.16.3)

project(protocol_compiler VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)


include_directories(.)

#        cmake-build-debug/protocol_compiler-prefix/src/protocol_compiler/Lexer.cpp
#        cmake-build-debug/protocol_compiler-prefix/src/protocol_compiler/LexerToken.cpp
#        cmake-build-debug/protocol_compiler-prefix/src/protocol_compiler/Token.cpp
#        cmake-build-debug/protocol_compiler-prefix/src/protocol_compiler/GrammarToken.cpp read_write/Proxy.h)


include(GNUInstallDirs)

add_library(pc SHARED
        CodeGen.h
        ParserAction.h
        GrammarToken.cpp
        GrammarToken.h
        Grammar.h
        Lexer.cpp
        LexerToken.cpp
        Production.h
        Token.cpp
        Node.h
        ParseException.h
        Util.h
        Lexer.h
        Util.cpp)

set_target_properties(pc PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 2
        PUBLIC_HEADER "CodeGen.h;ParserAction.h;Grammar.h;Production.h;Node.h;ParseException.h;GrammarToken.h;Util.h;Token.h;LexerToken.h;Lexer.h")

target_include_directories(pc PRIVATE .)

install(TARGETS pc
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(parser
        lang/protocol/code_gen/ProtocolClass.h
        lang/protocol/code_gen/Generator.h
        lang/protocol/Tokens.h
        lang/protocol/LexerDefs.h
        lang/protocol/GrammarDefs.h
        lang/protocol/Tokens.cpp
        main.cpp
        lang/protocol/code_gen/parse_primitives/Bitmap.cpp
        lang/protocol/code_gen/parse_primitives/Bitmap.h
        lang/protocol/code_gen/parse_primitives/Field.cpp
        lang/protocol/code_gen/parse_primitives/Field.h
        lang/protocol/code_gen/parse_primitives/While.cpp
        lang/protocol/code_gen/parse_primitives/While.h
        lang/protocol/code_gen/parse_primitives/Expression.h
        lang/protocol/code_gen/parse_primitives/Expression.cpp
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
        lang/protocol/code_gen/parse_primitives/FieldExpr.cpp
        lang/protocol/code_gen/parse_primitives/FieldExpr.h
        lang/protocol/code_gen/parse_primitives/NextProtocol.cpp
        lang/protocol/code_gen/parse_primitives/NextProtocol.h
        lang/protocol/code_gen/BuildClass.cpp
        lang/protocol/code_gen/BuildClass.h
        lang/protocol/code_gen/ProtocolUtil.h)

add_dependencies(parser pc)
target_link_libraries(parser pc)

