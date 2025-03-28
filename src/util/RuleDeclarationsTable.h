#ifndef MINIMALISTIC_PARSER_GENERATOR_RULEDECLARATIONSTABLE_H
#define MINIMALISTIC_PARSER_GENERATOR_RULEDECLARATIONSTABLE_H


#include <memory>

#include <set>
#include "../lexer/Token.h"

class RuleDeclarationsTable {
    std::set<std::shared_ptr<Token>> rules;
public:
    bool declare(const std::shared_ptr<Token>& rule);
};


#endif //MINIMALISTIC_PARSER_GENERATOR_RULEDECLARATIONSTABLE_H
