#ifndef MINIMALISTIC_PARSER_GENERATOR_STRUCT_MAPPING_H
#define MINIMALISTIC_PARSER_GENERATOR_STRUCT_MAPPING_H

#include <string>
#include <memory>
#include <vector>

class Token {
    std::string body;
};

class Node {
    std::vector<Token> tokens;
    std::vector<std::shared_ptr<Node>> children;
};

#endif //MINIMALISTIC_PARSER_GENERATOR_STRUCT_MAPPING_H
