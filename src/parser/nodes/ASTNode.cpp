#include <sstream>
#include "ASTNode.h"

void ASTNode::appendChild(std::shared_ptr<ASTNode> node) {
    this->children.push_back(node);
}

std::string ASTNode::toString() const {
    std::stringstream ss;
    ss << "{" << std::endl;
    for(auto &n : children) {
        ss << n->toString() << std::endl;
    }
    ss << "}";
    return ss.str();
}

void ASTNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<ASTNode>(*this));
}

std::shared_ptr<ASTNode> ASTNode::operator[](int idx) {
    return children[idx];
}

const std::vector<std::shared_ptr<ASTNode>> &ASTNode::getChildren() const {
    return children;
}

std::string ASTNode::terminate(std::string nodeName) const {
    return std::string();
}

std::string ASTNode::wrap(std::map<std::string, std::string>& aliases) const {
    return "1";
}


