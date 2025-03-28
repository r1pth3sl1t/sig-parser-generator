#ifndef MINIMALISTIC_PARSER_GENERATOR_ASTNODE_H
#define MINIMALISTIC_PARSER_GENERATOR_ASTNODE_H


#include <memory>
#include <vector>
#include <map>
#include "ASTVisitor.h"

class ASTNode {
protected:
    std::vector<std::shared_ptr<ASTNode>> children;
public:
    const std::vector<std::shared_ptr<ASTNode>> &getChildren() const;

public:
    void appendChild(std::shared_ptr<ASTNode> node);
    virtual std::string toString() const;
    virtual void accept(ASTVisitor &visitor) const;
    std::shared_ptr<ASTNode> operator[](int idx);
    virtual std::string terminate(std::string nodeName) const;
    virtual std::string wrap(std::map<std::string, std::string>& aliases) const;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_ASTNODE_H
