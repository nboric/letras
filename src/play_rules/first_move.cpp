//
// Created by Neven Boric on 5/7/25.
//

#include "first_move.h"
const std::string_view& FirstMove::getName() const
{
    return NAME;
}

bool FirstMove::isValid(Play& play, const Board& board, std::optional<std::string>& reason) const
{
    if (board.isSquareFree(BoardImpl::center_coords_))
    {
        if (!play.placement_map.contains(BoardImpl::center_coords_))
        {
            if (reason)
            {
                *reason = "First move must occupy center square";
            }
            return false;
        }
        play.is_first = true;
    }
    return true;
}
