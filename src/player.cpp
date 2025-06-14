//
// Created by Neven Boric on 4/19/25.
//

#include "player.h"

void Player::replenish(Bag& bag)
{
    const size_t needed = MAX_TILES - tiles_.size();
    if (needed == 0)
    {
        return;
    }
    for (int i = 0; i < needed; i++)
    {
        tiles_.push_back(std::move(bag.takeOne()));
    }
}

void Player::addScore(const int score)
{
    score_.addScore(score);
}

void Player::takeAll(std::vector<std::unique_ptr<Tile> >& tiles)
{
    while (!tiles.empty())
    {
        tiles_.push_back(std::move(tiles.back()));
        tiles.pop_back();
    }
}