//
// Created by nbori on 6/14/2025.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "../board.h"
#include "../dict.h"
#include "../play_rules/play_builder.h"

class Algorithm
{
    std::shared_ptr<const Dict> dict_;
    const PlayBuilder play_builder_;

public:
    explicit Algorithm(const std::shared_ptr<const Dict>& dict);
    void findAvailablePlays(Board& board, std::vector<Tile>& tiles) const;

    static void getStartPositions(std::vector<int>& starting_positions, int n_tiles);
    static void getCoords(std::vector<Coords>& coords_list, Direction direction, const Coords& existing_tile_coords,
        int starting_position, int n_tiles);
};

inline void Algorithm::getStartPositions(std::vector<int>& starting_positions, const int n_tiles)
{
    for (int start = 1; start > -n_tiles; --start)
    {
        if (start == 0)
        {
            continue;
        }
        starting_positions.push_back(start);
    }
}

inline void Algorithm::getCoords(std::vector<Coords>& coords_list, const Direction direction,
    const Coords& existing_tile_coords,
    const int starting_position,
    const int n_tiles)
{
    for (int pos = 0, i = 0; i < n_tiles; ++i, ++pos)
    {
        Coords coords;
        if (starting_position + pos == 0)
        {
            pos++;
        }
        auto const delta_pos = starting_position + pos;
        if (direction == VERTICAL)
        {
            coords = { existing_tile_coords.first + delta_pos, existing_tile_coords.second };
        }
        else
        {
            coords = { existing_tile_coords.first, existing_tile_coords.second + delta_pos };
        }
        coords_list.push_back(coords);
    }
}

#endif //ALGORITHM_H
