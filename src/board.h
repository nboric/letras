//
// Created by Neven Boric on 4/19/25.
//

#ifndef BOARD_H
#define BOARD_H
#include <map>
#include <vector>

#include "square.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Board
{
    static constexpr int SIZE{ 15 };
    static constexpr int BORDER{ 20 };

    static const std::map<std::pair<int, int>, SquareDefinition> premium_squares_;

    std::vector<std::vector<Square> > squares_;

    static bool getSquareCoords(sf::Vector2i pos, std::pair<int, int>& coords);

public:
    Board();

    void draw(sf::RenderWindow& window, const sf::Font& font) const;
    [[nodiscard]] bool shouldHandleClick(sf::Vector2i pos) const;
    [[nodiscard]] bool canTakeTile(sf::Vector2i pos) const;
    void place(sf::Vector2i pos, std::unique_ptr<Tile>& tile);
};

#endif //BOARD_H
