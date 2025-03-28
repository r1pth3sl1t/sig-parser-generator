#ifndef MINIMALISTIC_PARSER_GENERATOR_ASTVISITOR_H
#define MINIMALISTIC_PARSER_GENERATOR_ASTVISITOR_H
#include <memory>

class ASTNode;
class RuleDeclarationNode;
class RuleDefinitionNode;
class TokenScanningRuleNode;
class RuleRecursiveCallNode;
class AliasDeclarationNode;
class DeclarationsNode;
class RuleNode;
class RunHandlerNode;

class ASTVisitor {
public:
    virtual void visit(std::shared_ptr<ASTNode> node) = 0;
    virtual void visit(std::shared_ptr<RuleNode> node) = 0;
    virtual void visit(std::shared_ptr<RuleDeclarationNode> node) = 0;
    virtual void visit(std::shared_ptr<RuleDefinitionNode> node) = 0;
    virtual void visit(std::shared_ptr<TokenScanningRuleNode> node) = 0;
    virtual void visit(std::shared_ptr<RuleRecursiveCallNode> node) = 0;
    virtual void visit(std::shared_ptr<AliasDeclarationNode> node) = 0;
    virtual void visit(std::shared_ptr<DeclarationsNode> node) = 0;
    virtual void visit(std::shared_ptr<RunHandlerNode> node) = 0;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_ASTVISITOR_H
