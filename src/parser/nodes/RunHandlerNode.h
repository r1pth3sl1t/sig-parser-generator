#ifndef MINIMALISTIC_PARSER_GENERATOR_RUNHANDLERNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_RUNHANDLERNODE_H


#include "ASTNode.h"
#include "../../lexer/Token.h"

class RunHandlerNode : public ASTNode {
    std::shared_ptr<Token> codeToRun;
public:
    const std::shared_ptr<Token> &getCodeToRun() const;

public:
    RunHandlerNode(std::shared_ptr<Token> token);

    virtual std::string toString() const;
    void accept(ASTVisitor &visitor) const override;
    virtual std::string wrap(std::map<std::string, std::string> &aliases) const override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_RUNHANDLERNODE_H
