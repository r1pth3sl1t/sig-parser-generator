#ifndef MINIMALISTIC_PARSER_GENERATOR_STRUCT_MAPPING_H
#define MINIMALISTIC_PARSER_GENERATOR_STRUCT_MAPPING_H

#include <string>
#include <memory>
#include <vector>

class Node {
public:
    std::string rule_name;
    std::vector<std::shared_ptr<Token>> tokens;
    std::vector<std::shared_ptr<Node>> children;
};

void error(std::string expected, const std::shared_ptr<Token>& actual , std::string rule);

#endif //MINIMALISTIC_PARSER_GENERATOR_STRUCT_MAPPING_H
