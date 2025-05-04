//
// Created by Neven Boric on 4/20/25.
//

#include "dict.h"

#include <fstream>

Dict::Dict(const std::string& path)
{
    std::ifstream dict_file(path);

    std::string line;
    while (std::getline(dict_file, line))
    {
        words_.insert(line);
    }
}

bool Dict::is_valid(const std::string& word) const
{
    return words_.contains(word);
}
