cmake_minimum_required(VERSION 3.27)
project(minimalistic_parser_generator)

set(CMAKE_CXX_STANDARD 17)

add_executable(minimalistic_parser_generator src/main.cpp
        src/lexer/Lexer.cpp
        src/lexer/Lexer.h
        src/lexer/Token.cpp
        src/lexer/Token.h
        src/lexer/Categories.cpp
        src/lexer/Categories.h
        src/util/Table.h
        src/parser/Parser.cpp
        src/parser/Parser.h
        src/parser/nodes/ASTNode.cpp
        src/parser/nodes/ASTNode.h
        src/parser/nodes/TokenScanningRuleNode.cpp
        src/parser/nodes/TokenScanningRuleNode.h
        src/parser/nodes/RuleRecursiveCallNode.cpp
        src/parser/nodes/RuleRecursiveCallNode.h
        src/util/RuleDeclarationsTable.cpp
        src/util/RuleDeclarationsTable.h
        src/util/RuleDeclarationsTable.h
        src/parser/nodes/AmbiguousRuleNode.cpp
        src/parser/nodes/AmbiguousRuleNode.h
        src/parser/nodes/RuleDeclarationNode.cpp
        src/parser/nodes/RuleDeclarationNode.h
        src/parser/nodes/RuleDefinitionNode.cpp
        src/parser/nodes/RuleDefinitionNode.h
        src/parser/nodes/RunHandlerNode.cpp
        src/parser/nodes/RunHandlerNode.h
        src/parser/nodes/RunHandlerNode.h
        src/codegen/CodeGenerator.cpp
        src/codegen/CodeGenerator.h
        src/parser/nodes/RuleNode.cpp
        src/parser/nodes/RuleNode.h
        src/parser/nodes/ASTVisitor.cpp
        src/parser/nodes/ASTVisitor.h
        src/test/struct_mapping.h
        src/parser/nodes/AliasDeclarationNode.cpp
        src/parser/nodes/AliasDeclarationNode.h
        src/parser/nodes/DeclarationsNode.cpp
        src/parser/nodes/DeclarationsNode.h
)
