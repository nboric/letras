//
// Created by Neven Boric on 5/4/25.
//

#include "contiguous.h"

#include <set>

const std::string_view& Contiguous::getName() const
{
    return NAME;
}

bool Contiguous::isValid(Play& play, const Board& board, std::string& reason) const
{
    if (play.moving_coord_values.size() == 1)
    {
        return true;
    }
    int prev = -1;
    if (play.all_i.size() != 1 && play.all_j.size() != 1)
    {
        reason = "Not strictly vertical or horizontal";
        return false;
    }
    for (auto const& coord : play.moving_coord_values)
    {
        if (prev != -1 && coord != prev + 1)
        {
            Coords coords = buildCoords(play, prev + 1);
            if (board.isSquareFree(coords))
            {
                reason = "Not contiguous";
                return false;
            }
        }
        prev = coord;
    }
    return true;
}
