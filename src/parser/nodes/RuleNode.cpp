//
// Created by пк on 27.03.2025.
//

#include <sstream>
#include "RuleNode.h"

std::string RuleNode::toString() const {
    std::stringstream ss;
    ss << "{rule ";
    for (auto &n : children) {
        ss << n->toString();
    }
    ss << "}";
    return ss.str();
}

void RuleNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<RuleNode>(*this));
}
