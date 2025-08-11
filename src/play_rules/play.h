//
// Created by Neven Boric on 5/7/25.
//

#ifndef PLAY_H
#define PLAY_H

#include <set>
#include <map>

#include "../basic_types.h"
#include "../board.h"

class Play
{
    bool is_valid_{ false };
    void initialize();

public:
    explicit Play(const Board& board);
    explicit Play(const std::vector<Placement>& placements);

    Direction direction{ HORIZONTAL };

    std::set<int> all_i;
    std::set<int> all_j;

    int fixed_coord_value{ 0 };
    std::set<int> moving_coord_values;
    bool is_first{ false };
    int score{ 0 };

    std::vector<Placement> placements_;
    std::map<Coords, LetterLowercase> placement_map;
    std::map<Coords, LetterLowercase> complete_map;
};

#endif //PLAY_H
