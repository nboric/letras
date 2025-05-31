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
