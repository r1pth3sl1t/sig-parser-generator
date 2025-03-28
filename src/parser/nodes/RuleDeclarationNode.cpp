#include "RuleDeclarationNode.h"

#include <utility>

RuleDeclarationNode::RuleDeclarationNode(std::shared_ptr<Token> token) : ruleName(std::move(token)) {

}

std::string RuleDeclarationNode::toString() const {
    return "{declare " + ruleName->getBody() + "}";
}

void RuleDeclarationNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<RuleDeclarationNode>(*this));
}

const std::shared_ptr<Token> &RuleDeclarationNode::getRuleName() const {
    return ruleName;
}

void RuleDeclarationNode::setRuleName(const std::shared_ptr<Token> &ruleName) {
    RuleDeclarationNode::ruleName = ruleName;
}
