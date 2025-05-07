//
// Created by Neven Boric on 4/19/25.
//

#include "player.h"

#include <iostream>

Player::Player()
= default;

void Player::replenish(Bag& bag)
{
    const size_t needed = MAX_TILES - tiles_.size();
    if (needed == 0)
    {
        return;
    }
    for (int i = 0; i < needed; i++)
    {
        tiles_.push_back(std::move(bag.take_one()));
    }
}

void Player::draw(sf::RenderWindow& window, const sf::Font& font, const bool is_active,
    const sf::Vector2f base_pos) const
{
    if (is_active)
    {
        for (int i = 0; i < tiles_.size(); i++)
        {
            tiles_[i]->draw(window, font, base_pos + sf::Vector2f{ static_cast<float>(i * Tile::SIZE), 0 });
        }
    }
    score_.draw(window, font, base_pos + sf::Vector2f{ 0, Tile::SIZE + 10 });
}

void Player::handleClick(const sf::Vector2i pos) const
{
    for (const auto& tile : tiles_)
    {
        /* TODO: if I make the method void and not stop at the first match
         * we can select two tiles clicking at the border
         */
        tile->handleClick(pos);
    }
}

std::unique_ptr<Tile> Player::getSelectedTile()
{
    // TODO: don't iterate, save a reference
    for (int i = 0; i < tiles_.size(); i++)
    {
        if (tiles_[i]->isSelected())
        {
            std::unique_ptr<Tile> selected = std::move(tiles_[i]);
            tiles_.erase(tiles_.begin() + i);
            selected->setSelected(false);
            return selected;
        }
    }
    return nullptr;
}
