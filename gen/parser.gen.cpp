#include "parser.gen.h"

parser::parser(std::vector<std::shared_ptr<token>> &t) : tokens(t), tk(t.begin()) {};
std::shared_ptr<Node> parser::parse(){ return signal_program();}
std::shared_ptr<Node> parser::empty() {  std::shared_ptr<Node> node = std::make_shared<Node>(); node->rule_name = "empty"; return node; }
std::shared_ptr<Node> parser::signal_program()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "signal_program";
 if (try_program()) {
 node->children.push_back(program());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::program()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "program";
 if ((*tk)->content == "PROGRAM") {
 if ((*tk)->content != "PROGRAM") {
  error("PROGRAM", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(procedure_identifier());
 if ((*tk)->content != ";") {
  error(";", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(block());
 if ((*tk)->content != ".") {
  error(".", *tk, node->rule_name); return node;
 } else tk++;
 return node; }

 return node;
}

std::shared_ptr<Node> parser::block()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "block";
 if (try_declarations()) {
 node->children.push_back(declarations());
 if ((*tk)->content != "BEGIN") {
  error("BEGIN", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(statements_list());
 if ((*tk)->content != "END") {
  error("END", *tk, node->rule_name); return node;
 } else tk++;
 return node; }

 return node;
}

std::shared_ptr<Node> parser::declarations()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "declarations";
 if (try_label_declarations()) {
 node->children.push_back(label_declarations());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::label_declarations()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "label_declarations";
 if ((*tk)->content == "LABEL") {
 if ((*tk)->content != "LABEL") {
  error("LABEL", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(unsigned_integer());
 node->children.push_back(labels_list());
 if ((*tk)->content != ";") {
  error(";", *tk, node->rule_name); return node;
 } else tk++;
 return node; }
 if (try_empty()) {
 node->children.push_back(empty());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::labels_list()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "labels_list";
 if ((*tk)->content == ",") {
 if ((*tk)->content != ",") {
  error(",", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(unsigned_integer());
 node->children.push_back(labels_list());
 return node; }
 if (try_empty()) {
 node->children.push_back(empty());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::statements_list()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "statements_list";
 if (try_statement()) {
 node->children.push_back(statement());
 node->children.push_back(statements_list());
 return node; }
 if (try_empty()) {
 node->children.push_back(empty());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::statement()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "statement";
 if (try_unsigned_integer()) {
 node->children.push_back(unsigned_integer());
 if ((*tk)->content != ":") {
  error(":", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(statement());
 return node; }
 if (try_cond_statement()) {
 node->children.push_back(cond_statement());
 return node; }
 if (try_goto_statement()) {
 node->children.push_back(goto_statement());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::cond_statement()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "cond_statement";
 if (try_condition_statement()) {
 node->children.push_back(condition_statement());
 if ((*tk)->content != "ENDIF") {
  error("ENDIF", *tk, node->rule_name); return node;
 } else tk++;
 if ((*tk)->content != ";") {
  error(";", *tk, node->rule_name); return node;
 } else tk++;
 return node; }

 return node;
}

std::shared_ptr<Node> parser::goto_statement()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "goto_statement";
 if ((*tk)->content == "GOTO") {
 if ((*tk)->content != "GOTO") {
  error("GOTO", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(unsigned_integer());
 if ((*tk)->content != ";") {
  error(";", *tk, node->rule_name); return node;
 } else tk++;
 return node; }

 return node;
}

std::shared_ptr<Node> parser::condition_statement()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "condition_statement";
 if (try_incomplete_condition_statement()) {
 node->children.push_back(incomplete_condition_statement());
 node->children.push_back(alternative_part());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::incomplete_condition_statement()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "incomplete_condition_statement";
 if ((*tk)->content == "IF") {
 if ((*tk)->content != "IF") {
  error("IF", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(conditional_expression());
 if ((*tk)->content != "THEN") {
  error("THEN", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(statements_list());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::conditional_expression()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "conditional_expression";
 if (try_variable_identifier()) {
 node->children.push_back(variable_identifier());
 if ((*tk)->content != "=") {
  error("=", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(unsigned_integer());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::alternative_part()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "alternative_part";
 if (try_alt()) {
 node->children.push_back(alt());
 return node; }
 if (try_empty()) {
 node->children.push_back(empty());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::alt()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "alt";
 if ((*tk)->content == "ELSE") {
 if ((*tk)->content != "ELSE") {
  error("ELSE", *tk, node->rule_name); return node;
 } else tk++;
 node->children.push_back(statements_list());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::variable_identifier()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "variable_identifier";
 if (try_identifier()) {
 node->children.push_back(identifier());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::procedure_identifier()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "procedure_identifier";
 if (try_identifier()) {
 node->children.push_back(identifier());
 return node; }
 else { error("",*tk, node->rule_name); return node;}
 return node;
}

std::shared_ptr<Node> parser::identifier()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "identifier";
 if (
    (*tk)->token_code > 1000
) {
if (
    (*tk)->token_code > 1000
) 
{ node->tokens.push_back(*tk); 
 tk++; return node;} return node; }

 return node;
}

std::shared_ptr<Node> parser::unsigned_integer()
{
 std::shared_ptr<Node> node = std::make_shared<Node>();
 node->rule_name = "unsigned_integer";
 if (
    (*tk)->token_code > 500 && (*tk)->token_code < 1000
) {
if (
    (*tk)->token_code > 500 && (*tk)->token_code < 1000
) 
{ node->tokens.push_back(*tk); 
 tk++; return node;} return node; }

 return node;
}

