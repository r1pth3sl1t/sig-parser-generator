#ifndef MINIMALISTIC_PARSER_GENERATOR_RULERECURSIVECALLNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_RULERECURSIVECALLNODE_H


#include "ASTNode.h"
#include "../../lexer/Token.h"

class RuleRecursiveCallNode : public ASTNode {
    std::shared_ptr<Token> ruleToCall;
public:
    const std::shared_ptr<Token> &getRuleToCall() const;

public:
    RuleRecursiveCallNode(std::shared_ptr<Token> rule);
    std::string toString() const override;
    void accept(ASTVisitor &visitor) const override;
    virtual std::string terminate(std::string nodeName) const;
    virtual std::string wrap(std::map<std::string, std::string>& aliases) const override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_RULERECURSIVECALLNODE_H
