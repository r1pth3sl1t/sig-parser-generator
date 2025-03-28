#include "RunHandlerNode.h"

#include <utility>

RunHandlerNode::RunHandlerNode(std::shared_ptr<Token> token) : codeToRun(std::move(token)) {

}

std::string RunHandlerNode::toString() const {
    return "{invoke " + codeToRun->getBody() + "}";
}

void RunHandlerNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<RunHandlerNode>(*this));
}

const std::shared_ptr<Token> &RunHandlerNode::getCodeToRun() const {
    return codeToRun;
}

std::string RunHandlerNode::wrap(std::map<std::string, std::string> &aliases) const {
    return codeToRun->getBody();
}
