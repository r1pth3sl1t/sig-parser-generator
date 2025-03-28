#ifndef MINIMALISTIC_PARSER_GENERATOR_DECLARATIONSNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_DECLARATIONSNODE_H


#include "ASTNode.h"

class DeclarationsNode : public ASTNode {
public:
    virtual std::string toString() const override;
    void accept(ASTVisitor &visitor) const override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_DECLARATIONSNODE_H
