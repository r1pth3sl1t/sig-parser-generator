#include "RuleRecursiveCallNode.h"

RuleRecursiveCallNode::RuleRecursiveCallNode(std::shared_ptr<Token> rule) : ruleToCall(rule){

}

std::string RuleRecursiveCallNode::toString() const {
    return "{call " + ruleToCall->getBody() + "}";
}

void RuleRecursiveCallNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<RuleRecursiveCallNode>(*this));
}

const std::shared_ptr<Token> &RuleRecursiveCallNode::getRuleToCall() const {
    return ruleToCall;
}

std::string RuleRecursiveCallNode::terminate(std::string nodeName) const {
    return " else { error(\"\",*tk, node->" + nodeName + "); return node;}";
}

std::string RuleRecursiveCallNode::wrap(std::map<std::string, std::string>&) const {
    return "try_" + ruleToCall->getBody() + "()";
}

