#include <iostream>
#include "Parser.h"
#include "nodes/TokenScanningRuleNode.h"
#include "nodes/RuleRecursiveCallNode.h"
#include "nodes/RuleDeclarationNode.h"
#include "nodes/RuleDefinitionNode.h"
#include "nodes/RunHandlerNode.h"
#include "nodes/RuleNode.h"
#include "nodes/AliasDeclarationNode.h"
#include "nodes/DeclarationsNode.h"

Parser::Parser(std::vector<std::shared_ptr<Token>> &_tokens) : tokens(_tokens), iterator(_tokens.begin()){

}

std::shared_ptr<ASTNode> Parser::parse() {
    std::shared_ptr<ASTNode> mainNode = std::make_shared<ASTNode>();
    while (iterator != tokens.end()) {
        std::cout << currentToken()->getBody() << std::endl;
        if (currentToken()->getCode() == '<')
            mainNode->appendChild(rule());
        else mainNode->appendChild(declarations());
    }
    return mainNode;
}

std::shared_ptr<ASTNode> Parser::rule() {
    std::shared_ptr<RuleNode> ruleNode = std::make_shared<RuleNode>();
    std::shared_ptr<Token> tk;
    ruleNode->appendChild(ruleDeclaration());
    tk = nextToken();

    if (tk->getCode() == 301) {
        tk = nextToken();

        std::shared_ptr<RuleDefinitionNode> ruleDefinition = std::make_shared<RuleDefinitionNode>();
        do {
            while (tk->getCode() != '|' && tk->getCode() != ';') {
                if (tk->getCode() > 100000) {
                    ruleDefinition->appendChild(std::make_shared<RunHandlerNode>(tk));
                    tk = nextToken();
                }
                if (tk->getCode() > 10000) {
                    ruleDefinition->appendChild(std::make_shared<TokenScanningRuleNode>(tk));
                    tk = nextToken();
                }
                if (tk->getCode() == '<') {
                    tk = nextToken();
                    if (tk->getCode() > 1000) {
                        ruleDefinition->appendChild(std::make_shared<RuleRecursiveCallNode>(tk));
                    }
                    tk = nextToken();
                    if (tk->getCode() == '>') {

                    }
                    tk = nextToken();

                }

            }
            ruleNode->appendChild(ruleDefinition);
            if (tk->getCode() == '|') {
                tk = nextToken();
                ruleDefinition = std::make_shared<RuleDefinitionNode>();
            }

        } while (tk && tk->getCode() != ';');
    }
    return ruleNode;
}

std::shared_ptr<Token> Parser::nextToken() {
    return *(iterator++);
}

std::shared_ptr<ASTNode> Parser::ruleDeclaration() {
    std::shared_ptr<ASTNode> node;
    std::shared_ptr<Token> tk = nextToken();
    if (tk->getCode() == '<') {
        tk = nextToken();
        if (tk->getCode() > 1000 && tk->getCode() < 10000) {
            node = std::make_shared<RuleDeclarationNode>(tk);
        }
        tk = nextToken();
        if (tk->getCode() == '>') {

        }
    }

    return node;
}

std::shared_ptr<Token> Parser::currentToken() {
    return *iterator;
}

std::shared_ptr<ASTNode> Parser::alias() {
    auto t1 = nextToken();
    nextToken();
    auto t2 = nextToken();
    std::shared_ptr<ASTNode> aliasNode = std::make_shared<AliasDeclarationNode>(t1, t2);
    nextToken();
    return aliasNode;
}

std::shared_ptr<ASTNode> Parser::declarations() {
    std::shared_ptr<DeclarationsNode> declNode = std::make_shared<DeclarationsNode>();
    while (iterator != tokens.end() && currentToken()->getCode() != '<') {
        declNode->appendChild(alias());
    }
    return declNode;
}


