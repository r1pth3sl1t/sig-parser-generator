#ifndef MINIMALISTIC_PARSER_GENERATOR_LEXER_H
#define MINIMALISTIC_PARSER_GENERATOR_LEXER_H


#include <vector>
#include <fstream>
#include <memory>
#include "Token.h"
#include "Categories.h"
#include "../util/Table.h"

class Lexer {
    std::istream &istream;
    Categories categories;
    RulesTable rulesTable;
    UserDefinedTokens userDefinedTokens;
    MulticharDelimiters multicharDelimiters;
    TerminalHandlerCodes terminalHandlerCodes;
    char current;
    char next();
public:
    explicit Lexer(std::istream &istream);
    std::vector<std::shared_ptr<Token>> tokenize();
};


#endif //MINIMALISTIC_PARSER_GENERATOR_LEXER_H
