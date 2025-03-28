#ifndef MINIMALISTIC_PARSER_GENERATOR_ALIASDECLARATIONNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_ALIASDECLARATIONNODE_H


#include "ASTNode.h"
#include "../../lexer/Token.h"

class AliasDeclarationNode : public ASTNode {
    std::shared_ptr<Token> tokenToReplace, alias;
public:
    const std::shared_ptr<Token> &getTokenToReplace() const;

    void setTokenToReplace(const std::shared_ptr<Token> &tokenToReplace);

    const std::shared_ptr<Token> &getAlias() const;

    void setAlias(const std::shared_ptr<Token> &alias);

public:
    AliasDeclarationNode(const std::shared_ptr<Token> &tokenToReplace, const std::shared_ptr<Token> &alias);
    virtual std::string toString() const override;
    virtual void accept(ASTVisitor &visitor) const override;

};


#endif //MINIMALISTIC_PARSER_GENERATOR_ALIASDECLARATIONNODE_H
