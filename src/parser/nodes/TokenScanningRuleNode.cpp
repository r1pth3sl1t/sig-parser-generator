#include "TokenScanningRuleNode.h"

#include <utility>
#include <sstream>

TokenScanningRuleNode::TokenScanningRuleNode(std::shared_ptr<Token> token) : tokenToScan(std::move(token)) {

}

std::string TokenScanningRuleNode::toString() const {
    return "{scan " + tokenToScan->getBody() + "}";
}

void TokenScanningRuleNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<TokenScanningRuleNode>(*this));
}

const std::shared_ptr<Token> &TokenScanningRuleNode::getTokenToScan() const {
    return tokenToScan;
}

std::string TokenScanningRuleNode::wrap(std::map<std::string, std::string>& aliases) const {
    return "(*tk)->" + aliases["token_body"] + " == \"" + tokenToScan->getBody() + "\"";
}
