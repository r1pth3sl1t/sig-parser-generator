//
// Created by пк on 28.03.2025.
//

#include "AliasDeclarationNode.h"

AliasDeclarationNode::AliasDeclarationNode(const std::shared_ptr<Token> &tokenToReplace,
                                           const std::shared_ptr<Token> &alias) : tokenToReplace(tokenToReplace),
                                                                                  alias(alias) {}

std::string AliasDeclarationNode::toString() const {
    return "{declare alias " + tokenToReplace->getBody() + ", " + alias->getBody() + "}";
}

void AliasDeclarationNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<AliasDeclarationNode>(*this));
}

const std::shared_ptr<Token> &AliasDeclarationNode::getTokenToReplace() const {
    return tokenToReplace;
}

void AliasDeclarationNode::setTokenToReplace(const std::shared_ptr<Token> &tokenToReplace) {
    AliasDeclarationNode::tokenToReplace = tokenToReplace;
}

const std::shared_ptr<Token> &AliasDeclarationNode::getAlias() const {
    return alias;
}

void AliasDeclarationNode::setAlias(const std::shared_ptr<Token> &alias) {
    AliasDeclarationNode::alias = alias;
}
