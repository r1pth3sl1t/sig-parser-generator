#include <iostream>
#include "CodeGenerator.h"
#include "../parser/nodes/RuleDeclarationNode.h"
#include "../parser/nodes/AliasDeclarationNode.h"
#include "../parser/nodes/DeclarationsNode.h"
#include "../parser/nodes/RuleDefinitionNode.h"
#include "../parser/nodes/RuleNode.h"
#include "../parser/nodes/RuleRecursiveCallNode.h"
#include "../parser/nodes/TokenScanningRuleNode.h"
#include "../parser/nodes/RunHandlerNode.h"


CodeGenerator::CodeGenerator(std::shared_ptr<ASTNode> node) : masterNode(std::move(node)), header("../gen/parser.gen.h"),
                                                              source("../gen/parser.gen.cpp"), try_file("../gen/try_methods.gen.cpp"){
    aliases = {
            {"token", "token"},
            {"node", "node"},
            {"token_body", "token_body"},
            {"node_name", "node_name"},
            {"node_children", "node_children"},
            {"node_tokens", "node_tokens"},
            {"parser", "parser"},
            {"parse", "parse"},
            {"decl_header", "decl_header"},
            {"root_rule", "root_rule"}
    };
}

void CodeGenerator::generate() {
    visit(masterNode);

}

void CodeGenerator::visit(std::shared_ptr<ASTNode> node) {

    (*node)[0]->accept(*this);
    header << "#include <vector>\n"
              "#include <memory>\n"
              "#include <string>\n"
              "#include \"" << aliases["decl_header"] <<  ".h\"\n";

    try_file << "#include \"parser.gen.h\"" << std::endl;

    header << "class " << aliases["parser"] << " {\n"
              "std::vector<std::shared_ptr<" << aliases["token"] << ">> &tokens; std::vector<std::shared_ptr<" << aliases["token"] << ">>::iterator tk;\n"
              "public:\n"
              " std::shared_ptr<" << aliases["node"] << "> empty();\n" <<
              " bool try_empty();\n"
              " " << aliases["parser"] << "(std::vector<std::shared_ptr<" << aliases["token"] << ">> &tokens);\n"
              " std::shared_ptr<" << aliases["node"] << "> " << aliases["parse"] << "();\n";
    source << "#include \"parser.gen.h\"\n\n";
    source << aliases["parser"] << "::" << aliases["parser"] << "(std::vector<std::shared_ptr<" << aliases["token"] << ">> &t) : tokens(t), tk(t.begin()) {};\n";
    source << "std::shared_ptr<" << aliases["node"] << "> "<< aliases["parser"] << "::" << aliases["parse"] << "(){ return " << aliases["root_rule"] << "();}" << std::endl;

    source << "std::shared_ptr<" << aliases["node"] << "> " << aliases["parser"] << "::empty() { " <<
    " std::shared_ptr<" << aliases["node"] << "> node = std::make_shared<" << aliases["node"] << ">();" <<
    " node->" << aliases["node_name"] << " = \"empty\"; return node; }" << std::endl;
    try_file << "bool " << aliases["parser"] << "::try_empty() { return true;}" << std::endl;

    for (int i = 1; i < node->getChildren().size(); ++i) {
        (*node)[i]->accept(*this);
    }
    header << "};\n";
}

void CodeGenerator::visit(std::shared_ptr<RuleDeclarationNode> node) {
    header << " std::shared_ptr<" << aliases["node"] << "> " << node->getRuleName()->getBody() << "();" << std::endl;
    header << " bool try_" << node->getRuleName()->getBody() << "();" << std::endl;
    source << "std::shared_ptr<" << aliases["node"] << "> " << aliases["parser"] << "::" << node->getRuleName()->getBody() << "()" << std::endl;
    source << "{" << std::endl;
    source << " std::shared_ptr<" << aliases["node"] << "> node = std::make_shared<" << aliases["node"] << ">();" << std::endl;
    source << " node->" << aliases["node_name"] << " = \"" << node->getRuleName()->getBody() << "\";" << std::endl;
    try_file << "bool " << aliases["parser"] << "::try_" << node->getRuleName()->getBody() << "() {" << std::endl;
}

void CodeGenerator::visit(std::shared_ptr<RuleDefinitionNode> node) {
    source << " if (" << (*node)[0]->wrap(aliases) << ") {"  << std::endl;
    try_file << " if (" << (*node)[0]->wrap(aliases) << ") {\n return true;\n } "  << std::endl;
    for (auto &n : node->getChildren()) {
        n->accept(*this);
    }
    source << " return node; }" << std::endl;
}

void CodeGenerator::visit(std::shared_ptr<TokenScanningRuleNode> node) {
    source << " if ((*tk)->" << aliases["token_body"] << " != \"" << node->getTokenToScan()->getBody() << "\") {" << std::endl;
    source << "  error(\"" << node->getTokenToScan()->getBody() << "\", *tk, node->" << aliases["node_name"] << "); return node;" << std::endl;
    source << " } else tk++;" << std::endl;

}

void CodeGenerator::visit(std::shared_ptr<RuleRecursiveCallNode> node) {
    source << " node->" << aliases["node_children"] << ".push_back(" <<  node->getRuleToCall()->getBody() << "());" << std::endl;

    /*try_file << " if(try_" << node->getRuleToCall()->getBody() << "()) {" << std::endl;
    try_file << " return true; };" << std::endl;*/
}

void CodeGenerator::visit(std::shared_ptr<AliasDeclarationNode> node) {

    if (aliases.count(node->getTokenToReplace()->getBody())) {
        aliases[node->getTokenToReplace()->getBody()] = node->getAlias()->getBody();
    }
}

void CodeGenerator::visit(std::shared_ptr<DeclarationsNode> node) {
    for (auto &n : node->getChildren()) {
        n->accept(*this);
    }
}

void CodeGenerator::visit(std::shared_ptr<RuleNode> node) {
    (*node)[0]->accept(*this);
    for (int i = 1; i < node->getChildren().size(); ++i) {
        (*node)[i]->accept(*this);
    }
    std::shared_ptr<ASTNode> lastDef = (*node)[node->getChildren().size() - 1];
    source << (*lastDef)[lastDef->getChildren().size() - 1]->terminate(aliases["node_name"]) << std::endl;
    source << " return node;" << std::endl;
    source << "}" << std::endl << std::endl;

    try_file << " return false;" << std::endl;
    try_file << "}" << std::endl << std::endl;
}

void CodeGenerator::generateRuleDeclarations(const std::vector<std::shared_ptr<ASTNode>> &rules) const {
    for (auto &rule : rules) {
        rule->accept((ASTVisitor &) *this);
    }
}

void CodeGenerator::visit(std::shared_ptr<RunHandlerNode> node) {
    source << "if (" << node->getCodeToRun()->getBody() << ") " << std::endl <<
    "{ node->" << aliases["node_tokens"] << ".push_back(*tk); " << std::endl <<
    " tk++; return node;}";
}

void CodeGenerator::generateTryRuleDeclarationCheckup(std::shared_ptr<RuleNode> &rule) const {


}
