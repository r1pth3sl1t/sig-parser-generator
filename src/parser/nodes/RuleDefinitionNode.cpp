//
// Created by пк on 27.03.2025.
//

#include <sstream>
#include "RuleDefinitionNode.h"

std::string RuleDefinitionNode::toString() const {
    std::stringstream ss;
    ss << "{define ";
    for(auto &n : children) {
        ss << n->toString();
    }
    ss << "}";
    return ss.str();
}

void RuleDefinitionNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<RuleDefinitionNode>(*this));
}

std::string RuleDefinitionNode::wrap(std::map<std::string, std::string>& aliases) const {
    return children[0]->wrap(aliases);
}
