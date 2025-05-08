//
// Created by Neven Boric on 4/19/25.
//

#ifndef BOARD_H
#define BOARD_H
#include <map>
#include <vector>

#include "basic_types.h"
#include "square.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Board
{
    static constexpr int SIZE{ 15 };
    static constexpr int BORDER{ 20 };

    static const std::map<Coord, SquareDefinition> premium_squares_;

    std::vector<std::vector<Square> > squares_;

    static bool getSquareCoords(sf::Vector2i pos, Coord& coords);

public:
    Board();

    static constexpr Coord center_coords_{ SIZE / 2, SIZE / 2 };

    void draw(sf::RenderWindow& window, const sf::Font& font) const;
    [[nodiscard]] bool shouldHandleClick(sf::Vector2i pos) const;
    [[nodiscard]] bool canTakeTile(sf::Vector2i pos) const;
    void placeTemp(sf::Vector2i pos, std::unique_ptr<Tile>& tile);
    void getPlacements(std::vector<Placement>& placements) const;
    void acceptPlacements();
    [[nodiscard]] bool isTileFree(const Coord& coords) const;
};

#endif //BOARD_H
