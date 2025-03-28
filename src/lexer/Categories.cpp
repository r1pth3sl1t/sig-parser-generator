#include <algorithm>
#include <iostream>
#include "Categories.h"

Categories::SymbolCategory Categories::operator[](char idx) const {
    if (idx <= 0) return SymbolCategory::DENIED;
    return categories[idx];
}

Categories::Categories() {
    std::fill(categories, categories + 128, SymbolCategory::DENIED);
    for (int i = 8; i < 14; ++i) {
        categories[i] = SymbolCategory::WHITESPACE;
    }
    categories[' '] = SymbolCategory::WHITESPACE;
    for (int i = 48; i < 58; ++i) {
        categories[i] = SymbolCategory::DIGIT;
    }
    for (int i = 64; i < 91; ++i) {
        categories[i] = SymbolCategory::LETTER;
    }
    for (int i = 97; i < 123; ++i) {
        categories[i] = SymbolCategory::LETTER;
    }
    categories['_'] = SymbolCategory::LETTER;
    categories['/'] = SymbolCategory::LETTER;
    categories['$'] = SymbolCategory::LETTER;
    categories['='] = SymbolCategory::DELIMITER;
    categories[';'] = SymbolCategory::DELIMITER;
    categories['<'] = SymbolCategory::DELIMITER;
    categories['>'] = SymbolCategory::DELIMITER;
    categories['|'] = SymbolCategory::DELIMITER;
    categories['{'] = SymbolCategory::FIGURE_BRACKET;
    categories['.'] = SymbolCategory::MDELIMITER;
    categories['-'] = SymbolCategory::MDELIMITER;
    categories['\''] = SymbolCategory::QUOTE;
}
