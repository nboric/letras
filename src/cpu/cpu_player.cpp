//
// Created by nbori on 6/14/2025.
//

#include "cpu_player.h"

CpuPlayer::CpuPlayer(const std::shared_ptr<Dict>& dict): algorithm_(dict)
{

}


bool CpuPlayer::isInteractive() const
{
    return false;
}

Action CpuPlayer::getAction(const Board& board) const
{
    return PLAY;
}

void CpuPlayer::draw(sf::RenderWindow& window, const sf::Font& font, bool is_active, sf::Vector2f base_pos) const
{
    score_.draw(window, font, base_pos + sf::Vector2f{ 0, Tile::SIZE + 10 });
}

void CpuPlayer::handleClick(sf::Vector2i pos, bool is_exchanging) const
{
}

std::unique_ptr<Tile> CpuPlayer::getSelectedTile()
{
    return nullptr;
}

void CpuPlayer::unselectAll() const
{
}

void CpuPlayer::exchange(Bag& bag)
{
}

void CpuPlayer::generatePlacements(Board& board)
{
    std::vector<Placement> placements;
    unsigned char selection_mask;
    auto word = algorithm_.findBestPlay(board, tiles_, placements, selection_mask);

    board.placeTemp(tiles_, placements, selection_mask);
    for (auto it = tiles_.begin(); it != tiles_.end();)
    {
        if (*it == nullptr)
        {
            it = tiles_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
