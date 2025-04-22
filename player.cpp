//
// Created by Neven Boric on 4/19/25.
//

#include "player.h"

#include <iostream>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

Player::Player()
{

}

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

void Player::draw(sf::RenderWindow& window, const sf::Font& font, const sf::Vector2f base_pos) const
{
    for (int i = 0; i < tiles_.size(); i++)
    {
        tiles_[i]->draw(window, font, base_pos + sf::Vector2f{i * 50.f, 0});
    }

}
