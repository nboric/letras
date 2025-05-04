//
// Created by Neven Boric on 4/19/25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "bag.h"
#include "tile.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Player
{
    static constexpr int MAX_TILES{ 7 };
    std::vector<std::unique_ptr<Tile> > tiles_;

public:
    Player();
    void replenish(Bag& bag);
    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos) const;
    void handleClick(sf::Vector2i pos) const;
};

#endif //PLAYER_H
