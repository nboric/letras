//
// Created by Neven Boric on 5/7/25.
//

#include "play.h"

Play::Play(const Board& board)
{
    board.getPlacements(placements);
    // set is ordered, we use it to form word in right order
    for (const auto& [coord_, letter_] : placements)
    {
        all_i.insert(coord_.first);
        all_j.insert(coord_.second);
        placement_map.emplace(coord_, letter_);
        complete_map.emplace(coord_, letter_);
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
