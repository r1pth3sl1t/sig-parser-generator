//
// Created by пк on 27.03.2025.
//

#ifndef MINIMALISTIC_PARSER_GENERATOR_TOKENSCANNINGRULENODE_H
#define MINIMALISTIC_PARSER_GENERATOR_TOKENSCANNINGRULENODE_H


#include "ASTNode.h"
#include "../../lexer/Token.h"

class TokenScanningRuleNode : public ASTNode {
    std::shared_ptr<Token> tokenToScan;
public:
    const std::shared_ptr<Token> &getTokenToScan() const;

public:
    TokenScanningRuleNode(std::shared_ptr<Token> token);
    virtual std::string toString() const;
    void accept(ASTVisitor &visitor) const override;
    virtual std::string wrap(std::map<std::string, std::string>&) const override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_TOKENSCANNINGRULENODE_H
