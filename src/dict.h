//
// Created by Neven Boric on 4/20/25.
//

#ifndef DICT_H
#define DICT_H
#include <map>
#include <string>
#include <unordered_set>

#include "basic_types.h"

class Dict
{
    std::unordered_set<std::string> words_;
    std::map<LetterLowercase, std::unordered_set<std::string_view> > letter_filter_cache_;

public:
    explicit Dict(const std::string& path);

    std::unordered_set<std::string_view>& filterContaining(const LetterLowercase& letter);

    [[nodiscard]] bool is_valid(const std::string& word) const;
};

#endif //DICT_H
