//
// Created by nbori on 6/14/2025.
//

#include "algorithm.h"

#include <algorithm>
#include <numeric>

#include "../play_rules/play.h"
#include "../play_rules/play_builder.h"

Algorithm::Algorithm(const std::shared_ptr<const Dict>& dict): dict_(dict), play_builder_(dict_)
{

}

// TODO: a more optimal approach will be: for every occupied tile, get all possible words from dict that contain
// that letter are equal or shorter length than current n_tiles, then filter if the word can be formed with the tiles
// available, which will specify in which position the occupied tile must be used, then test if those fit in the board
// (pass rules)
// creating som JIT caches inside the dict
void Algorithm::findAvailablePlays(Board& board, std::vector<Tile>& tiles) const
{
    // TODO: also need to iterate over number of tiles picked
    auto n_tiles = tiles.size();
    std::vector<Placement> occupied_tiles;
    board.getOccupied(occupied_tiles);
    std::vector<int> starting_positions;
    getStartPositions(starting_positions, n_tiles);
    for (const auto& placement : occupied_tiles)
    {
        for (auto direction: {HORIZONTAL, VERTICAL})
        {
            for (auto starting_position : starting_positions)
            {
                std::vector<int> indices;
                std::iota(indices.begin(), indices.end(), 0);
                do { // for each permutation of tiles
                    std::vector<Coords> coords_list;
                    getCoords(coords_list, direction, placement.coords_, starting_position, n_tiles);
                    for (int pos = 0; pos < n_tiles; ++pos)
                    {
                        auto tile = tiles[indices[pos]];
                        // board.placeTemp(coords, tile);
                        //                   std::vector<std::unique_ptr<Tile> > tiles;
                        // board_.returnPlacements(tiles);
                        // players_[current_player_]->takeAll(tiles);
                    }
                } while (std::ranges::next_permutation(indices).found);

            }
        }

        board.isSquareFree(placement.coords_);
        // board.placeTemp();
        Play play(board);
        std::optional<std::string> rule, reason; // purposely empty (can't use std::nullopt since it's const)
        if (!play_builder_.build(play, board, rule, reason))
        {

        }
        // Play play;
        placement.coords_;
    }
}
