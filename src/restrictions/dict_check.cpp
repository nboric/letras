//
// Created by Neven Boric on 5/4/25.
//

#include "dict_check.h"

#include <set>
#include <map>

#include "../dict.h"

const std::string& DictCheck::getName() const
{
    return NAME;
}

bool DictCheck::isValid(const std::vector<Placement>& placements, Dict& dict, std::string& reason) const
{
    // set is ordered, we use it to form word in right order
    std::set<int> all_i;
    std::set<int> all_j;
    std::map<std::pair<int, int>, std::wstring> placement_map;
    std::string word;
    for (const auto& [coord_, letter_] : placements)
    {
        all_i.insert(coord_.first);
        all_j.insert(coord_.second);
        placement_map.emplace(coord_, letter_);
    }
    if (all_i.size() != 1 && all_j.size() != 1)
    {
        return false;
    }
    enum
    {
        VERTICAL,
        HORIZONTAL
    } direction = HORIZONTAL;
    std::set<int>& fixed_coord = all_i;
    std::set<int>& moving_coords = all_j;
    if (all_j.size() == 1)
    {
        direction = VERTICAL;
        fixed_coord = all_j;
        moving_coords = all_i;
    }
    for (auto const& moving_coord : moving_coords)
    {
        std::pair<int, int> coord;
        if (direction == VERTICAL)
        {
            coord = { moving_coord, *fixed_coord.begin() };
        }
        else
        {
            coord = { *fixed_coord.begin(), moving_coord };
        }
        auto& letter = placement_map.at(coord);
        /* letter is wstring only to support displaying Ñ correctly in SFML, we don't allow any other wide chars
         * this also handles adding CH, LL, and RR, since we've always treated as a string of two letters
         */
        word.append(std::string(letter.begin(), letter.end()));
    }
    std::ranges::transform(word, word.begin(),
        [](const unsigned char c) { return std::tolower(c); });
    if (!dict.is_valid(word))
    {
        reason = "Word " + word + " not found in dictionary";
        return false;
    }
    return true;
}
