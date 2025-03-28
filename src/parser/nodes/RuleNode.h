
#ifndef MINIMALISTIC_PARSER_GENERATOR_RULENODE_H
#define MINIMALISTIC_PARSER_GENERATOR_RULENODE_H


#include "ASTNode.h"

class RuleNode : public ASTNode {
public:
    virtual std::string toString() const override;
    void accept(ASTVisitor &visitor) const override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_RULENODE_H
