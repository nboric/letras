//
// Created by Neven Boric on 4/20/25.
//

#include "dict.h"

#include <cassert>
#include <fstream>

Dict::Dict(const std::string& path)
{
    std::ifstream dict_file(path);

    std::string line;
    while (std::getline(dict_file, line))
    {
        line.erase(line.find_last_not_of('\r') + 1);
        words_.insert(line);
    }
    assert(!words_.empty());
}

bool Dict::is_valid(const std::string& word) const
{
    return words_.contains(word);
}

std::unordered_set<std::string_view>& Dict::filterContaining(const LetterLowercase& letter)
{
    if (!letter_filter_cache_.contains(letter))
    {
        std::unordered_set<std::string_view> filtered_words;
        for (const auto& word : words_)
        {
            if (word.find(letter) != std::string::npos)
            {
                filtered_words.insert(word);
            }
        }
        letter_filter_cache_.insert({ letter, filtered_words });
    }
    return letter_filter_cache_.at(letter);
}
