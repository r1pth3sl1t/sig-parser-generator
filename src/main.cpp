#include <iostream>
#include <fstream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "codegen/CodeGenerator.h"

int main() {
    std::ifstream file("../src/test/bnf-like.grammar");
    Lexer lexer(file);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    auto masterNode = parser.parse();
    std::cout << masterNode->toString() << std::endl;
    CodeGenerator codeGenerator(masterNode);
    codeGenerator.generate();
    return 0;
}
