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

    static const std::map<Coords, SquareDefinition> premium_squares_;

    std::vector<std::vector<Square> > squares_;

    static bool getSquareCoords(sf::Vector2i pos, Coords& coords);

public:
    Board();

    static constexpr Coords center_coords_{ SIZE / 2, SIZE / 2 };

    void draw(sf::RenderWindow& window, const sf::Font& font) const;
    [[nodiscard]] bool shouldHandleClick(sf::Vector2i pos) const;
    [[nodiscard]] bool canTakeTile(sf::Vector2i pos) const;
    void placeTemp(sf::Vector2i pos, std::unique_ptr<Tile>& tile);
    void getPlacements(std::vector<Placement>& placements) const;
    void acceptPlacements();
    [[nodiscard]] bool isSquareFree(const Coords& coords) const;
    bool getTileLetter(const Coords& coords, std::wstring& letter) const;
    bool getTileBaseScore(const Coords& coords, int& score) const;
    [[nodiscard]] std::optional<const SquareDefinition> getSquareDefinition(const Coords& coords) const;
};

#endif //BOARD_H
