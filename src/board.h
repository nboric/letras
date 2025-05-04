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
    static constexpr float BORDER{ 20.f };

    static const std::map<std::pair<int, int>, Square> premium_squares_;

    std::vector<std::vector<Square> > squares_;

public:
    Board();

    void draw(sf::RenderWindow& window) const;
};

#endif //BOARD_H
