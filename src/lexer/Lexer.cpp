#include <iostream>
#include "Lexer.h"

Lexer::Lexer(std::istream &_istream) : istream(_istream) {}

std::vector<std::shared_ptr<Token>> Lexer::tokenize() {
    std::vector<std::shared_ptr<Token>> tokens;
    std::string buf;
    bool isDecl = false;
    next();
    while (current != EOF) {
        switch (categories[current]) {
            case Categories::SymbolCategory::WHITESPACE:
                while (categories[current] == Categories::SymbolCategory::WHITESPACE) next();
                break;
            case Categories::SymbolCategory::LETTER:
                if (current == '$') {
                    isDecl = true;
                }
                else buf += current;
                next();
                while (categories[current] == Categories::SymbolCategory::LETTER ||
                        categories[current] == Categories::SymbolCategory::DIGIT) {
                    buf += current;
                    next();
                }

                tokens.push_back(std::make_shared<Token>(buf, rulesTable.push(buf)));
                buf.clear();
                break;
            case Categories::SymbolCategory::DELIMITER:
                tokens.push_back(std::make_shared<Token>(std::string(1, current), int(current)));
                next();
                break;
            case Categories::SymbolCategory::MDELIMITER:
                if (current == '-') {
                    next();
                    if (current == '-') {
                        next();
                        if (current == '>') {
                            next();
                            tokens.push_back(std::make_shared<Token>("-->", multicharDelimiters.getCode("-->")));
                        }
                    }
                }
                break;
            case Categories::SymbolCategory::DIGIT:
                break;
            case Categories::SymbolCategory::DENIED:
                next();
                break;
            case Categories::SymbolCategory::QUOTE:
                next();
                while (categories[current] != Categories::SymbolCategory::QUOTE) {
                    buf += current;
                    next();
                }
                tokens.push_back(std::make_shared<Token>(buf, userDefinedTokens.push(buf)));
                next();
                buf.clear();
                break;
            case Categories::SymbolCategory::FIGURE_BRACKET:
                next();
                while (current != '}') {
                    buf += current;
                    next();
                }
                tokens.push_back(std::make_shared<Token>(buf, terminalHandlerCodes.push(buf)));
                buf.clear();
        }
    }


    return tokens;
}

char Lexer::next() {
    current = (char)istream.get();
    return current;
}
