//
// Created by пк on 27.03.2025.
//

#include "RuleDeclarationsTable.h"

bool RuleDeclarationsTable::declare(const std::shared_ptr<Token>& rule) {
    bool declared = rules.count(rule);
    rules.insert(rule);
    return !declared;
}
