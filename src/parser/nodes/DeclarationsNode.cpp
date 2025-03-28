//
// Created by пк on 28.03.2025.
//

#include <sstream>
#include "DeclarationsNode.h"

std::string DeclarationsNode::toString() const {
    std::stringstream ss;
    ss << "{declare list of" << std::endl;
    for (auto &n : children) ss << n->toString() << std::endl;
    ss << "}\n";
    return ss.str();
}

void DeclarationsNode::accept(ASTVisitor &visitor) const {
    visitor.visit(std::make_shared<DeclarationsNode>(*this));
}
