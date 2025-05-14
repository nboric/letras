//
// Created by Neven Boric on 5/7/25.
//

#include "first_move.h"
const std::string& FirstMove::getName() const
{
    return NAME;
}

bool FirstMove::isValid(Play& play, const Board& board, std::string& reason) const
{
    if (board.isSquareFree(Board::center_coords_))
    {
        if (!play.placement_map.contains(Board::center_coords_))
        {
            reason = "First move must occupy center square";
            return false;
        }
        play.is_first = true;
    }
    return true;
}
