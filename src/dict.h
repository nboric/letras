//
// Created by Neven Boric on 4/20/25.
//

#ifndef DICT_H
#define DICT_H
#include <string>
#include <unordered_set>

class Dict
{
    std::unordered_set<std::string> words_;

public:
    explicit Dict(const std::string& path);

    [[nodiscard]] bool is_valid(const std::string& word) const;
};

#endif //DICT_H
