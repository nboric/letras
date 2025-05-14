//
// Created by Neven Boric on 5/7/25.
//

#include "play.h"

Play::Play(const Board& board)
{
    board.getPlacements(placements);
    // set is ordered, we use it to form word in right order
    for (const auto& [coords, letter] : placements)
    {
        all_i.insert(coords.first);
        all_j.insert(coords.second);
        placement_map.emplace(coords, letter);
        complete_map.emplace(coords, letter);
    }
    if (all_i.size() != 1 && all_j.size() != 1)
    {
        return;
    }
    if (all_i.size() == 1)
    {
        direction = HORIZONTAL;
        fixed_coord_value = *all_i.begin();
        // TODO: avoid copy
        moving_coord_values = all_j;
    }
    else
    {
        direction = VERTICAL;
        fixed_coord_value = *all_j.begin();
        // TODO: avoid copy
        moving_coord_values = all_i;
    }
    is_valid_ = true;
}
