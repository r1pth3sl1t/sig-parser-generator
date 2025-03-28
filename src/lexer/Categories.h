#ifndef MINIMALISTIC_PARSER_GENERATOR_CATEGORIES_H
#define MINIMALISTIC_PARSER_GENERATOR_CATEGORIES_H


class Categories {
public:
    enum class SymbolCategory : unsigned int {
        DENIED = 0,
        LETTER,
        DIGIT,
        WHITESPACE,
        DELIMITER,
        MDELIMITER,
        QUOTE,
        FIGURE_BRACKET
    };
private:
    SymbolCategory categories[128];
public:
    SymbolCategory operator[](char idx) const;
    Categories();
};


#endif //MINIMALISTIC_PARSER_GENERATOR_CATEGORIES_H
