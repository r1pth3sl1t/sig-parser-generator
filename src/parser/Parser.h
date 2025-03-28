#ifndef MINIMALISTIC_PARSER_GENERATOR_PARSER_H
#define MINIMALISTIC_PARSER_GENERATOR_PARSER_H


#include <vector>
#include <memory>
#include "../lexer/Token.h"
#include "nodes/ASTNode.h"
#include "../util/RuleDeclarationsTable.h"

class Parser {
    std::vector<std::shared_ptr<Token>> &tokens;
    std::vector<std::shared_ptr<Token>>::iterator iterator;
    RuleDeclarationsTable ruleDeclarationsTable;
    std::shared_ptr<ASTNode> declarations();
    std::shared_ptr<ASTNode> alias();
    std::shared_ptr<ASTNode> rule();
    std::shared_ptr<ASTNode> ruleDeclaration();
    std::shared_ptr<Token> nextToken();
    std::shared_ptr<Token> currentToken();
public:
    explicit Parser(std::vector<std::shared_ptr<Token>> &tokens);
    std::shared_ptr<ASTNode> parse();
};


#endif //MINIMALISTIC_PARSER_GENERATOR_PARSER_H
