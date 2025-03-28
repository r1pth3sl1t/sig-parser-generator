#ifndef MINIMALISTIC_PARSER_GENERATOR_TABLE_H
#define MINIMALISTIC_PARSER_GENERATOR_TABLE_H

#include <string>
#include <algorithm>
#include <vector>

template<int baseCode>
class Table {
protected:
    std::vector<std::string> table;
public:
    int push(const std::string& body) {
        auto idx = std::find(table.begin(), table.end(), body);
        if (idx == table.end()) {
            table.push_back(body);
            return baseCode + (int)table.size();
        }
        return baseCode + (int)(idx - table.begin()) + 1;
    }

    int getCode(const std::string& body) const {
        auto idx = std::find(table.begin(), table.end(), body);
        if (idx == table.end()) {
            return baseCode + (int)table.size();
        }
        return baseCode + (int)(idx - table.begin()) + 1;
    }

    const std::vector<std::string>& getTable() const {
        return table;
    };
};

class RulesTable : public Table<1000> {};
class UserDefinedTokens : public Table<10000> {};
class TerminalHandlerCodes : public Table<100000> {};
class MulticharDelimiters : public Table<300> {
public:
    MulticharDelimiters() {
        table.push_back("-->");
    }
};
#endif //MINIMALISTIC_PARSER_GENERATOR_TABLE_H
