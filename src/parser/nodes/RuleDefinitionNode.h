
#ifndef MINIMALISTIC_PARSER_GENERATOR_RULEDEFINITIONNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_RULEDEFINITIONNODE_H


#include "ASTNode.h"

class RuleDefinitionNode : public ASTNode{
public:
    virtual std::string toString() const;
    virtual void accept(ASTVisitor &visitor) const override;
    virtual std::string wrap(std::map<std::string, std::string>&) const override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_RULEDEFINITIONNODE_H
