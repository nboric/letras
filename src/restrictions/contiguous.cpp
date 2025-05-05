//
// Created by Neven Boric on 5/4/25.
//

#include "contiguous.h"

#include <set>

const std::string& Contiguous::getName() const
{
    return NAME;
}

bool Contiguous::isValid(const std::vector<Placement>& placements, Dict& dict, std::string& reason) const
{
    std::set<int> all_i;
    std::set<int> all_j;
    for (const auto& [coord_, letter_] : placements)
    {
        all_i.insert(coord_.first);
        all_j.insert(coord_.second);
    }
    if (all_i.size() != 1 && all_j.size() != 1)
    {
        reason = "Not strictly vertical or horizontal";
        return false;
    }
    std::set<int>& moving_coord = all_j;
    if (all_j.size() == 1)
    {
        moving_coord = all_i;
    }
    if (moving_coord.size() == 1)
    {
        return true;
    }
    int prev = -1;
    for (auto const& coord : moving_coord)
    {
        if (prev != -1 && coord != prev + 1)
        {
            reason = "Not contiguous";
            return false;
        }
        prev = coord;
    }
    return true;
}
