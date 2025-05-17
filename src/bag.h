//
// Created by Neven Boric on 4/19/25.
//

#ifndef BAG_H
#define BAG_H
#include <vector>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "tile.h"

class Bag
{
    static constexpr int SIZE{ 10 };
    static constexpr int HEIGHT{ 50 };
    std::vector<std::unique_ptr<Tile> > tiles_;

public:
    Bag();
    std::unique_ptr<Tile> takeOne();
    void putBack(std::unique_ptr<Tile>& tile);

    void draw(sf::RenderWindow& window, const sf::Font& font, sf::Vector2f base_pos) const;

    static const std::map<std::wstring, int> initial_quantities_;
};

#endif //BAG_H
