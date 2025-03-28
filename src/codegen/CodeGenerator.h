#ifndef MINIMALISTIC_PARSER_GENERATOR_CODEGENERATOR_H
#define MINIMALISTIC_PARSER_GENERATOR_CODEGENERATOR_H


#include <memory>
#include <fstream>
#include <map>
#include "../parser/nodes/ASTNode.h"
#include "../parser/nodes/ASTVisitor.h"

class CodeGenerator : ASTVisitor {
    std::shared_ptr<ASTNode> masterNode;
    std::ofstream header, source, try_file;
    std::map<std::string, std::string> aliases;
    void generateRuleDeclarations(const std::vector<std::shared_ptr<ASTNode>> &rules) const;
    void generateTryRuleDeclarationCheckup(std::shared_ptr<RuleNode> &rule) const;
public:
    CodeGenerator(std::shared_ptr<ASTNode> node);
    void generate();
    void visit(std::shared_ptr<ASTNode> node) override;
    virtual void visit(std::shared_ptr<RuleNode> node) override;
    void visit(std::shared_ptr<RuleDeclarationNode> node) override;
    void visit(std::shared_ptr<RuleDefinitionNode> node) override;
    void visit(std::shared_ptr<TokenScanningRuleNode> node) override;
    void visit(std::shared_ptr<RuleRecursiveCallNode> node) override;
    void visit(std::shared_ptr<RunHandlerNode> node) override;
    virtual void visit(std::shared_ptr<AliasDeclarationNode> node) override;
    virtual void visit(std::shared_ptr<DeclarationsNode> node) override;
};


#endif //MINIMALISTIC_PARSER_GENERATOR_CODEGENERATOR_H
