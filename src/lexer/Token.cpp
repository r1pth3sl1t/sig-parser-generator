//
// Created by пк on 27.03.2025.
//

#include "Token.h"

#include <utility>

const std::string &Token::getBody() const {
    return body;
}

void Token::setBody(const std::string &body) {
    Token::body = body;
}

int Token::getCode() const {
    return code;
}

void Token::setCode(int code) {
    Token::code = code;
}

Token::Token(std::string body, int code) : body(std::move(body)), code(code) {}
