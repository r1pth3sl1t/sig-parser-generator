#ifndef MINIMALISTIC_PARSER_GENERATOR_TOKEN_H
#define MINIMALISTIC_PARSER_GENERATOR_TOKEN_H


#include <string>

class Token {
    std::string body;
    int code;
public:
    const std::string &getBody() const;

    void setBody(const std::string &body);

    int getCode() const;

    void setCode(int code);

public:
    Token();

    Token(std::string body, int code);
};


#endif //MINIMALISTIC_PARSER_GENERATOR_TOKEN_H
