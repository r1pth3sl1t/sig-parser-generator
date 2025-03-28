//
// Created by пк on 27.03.2025.
//

#ifndef MINIMALISTIC_PARSER_GENERATOR_RULEDECLARATIONNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_RULEDECLARATIONNODE_H


#include "ASTNode.h"
#include "../../lexer/Token.h"

class RuleDeclarationNode : public ASTNode {
    std::shared_ptr<Token> ruleName;
public:
    RuleDeclarationNode(std::shared_ptr<Token> token);
    virtual std::string toString() const override;
    void accept(ASTVisitor &visitor) const override;

    const std::shared_ptr<Token> &getRuleName() const;

    void setRuleName(const std::shared_ptr<Token> &ruleName);
};


#endif //MINIMALISTIC_PARSER_GENERATOR_RULEDECLARATIONNODE_H
