//
// Created by Neven Boric on 5/16/25.
//

#ifndef MOCKS_H
#define MOCKS_H

#include <gmock/gmock.h>
#include "../src/board.h"

class BoardMock : public Board
{
public:
    MOCK_METHOD(void, draw, (sf::RenderWindow& window, const sf::Font& font), (const, override));
    MOCK_METHOD(std::optional<Coords>, shouldHandleClick, (sf::Vector2i pos), (const, override));
    MOCK_METHOD(bool, canTakeTile, (sf::Vector2i pos), (const, override));
    MOCK_METHOD(void, placeTemp, (sf::Vector2i pos, std::unique_ptr<Tile>& tile), (override));
    MOCK_METHOD(void, placeTemp, (Coords coords, std::unique_ptr<Tile>& tile), (override));
    MOCK_METHOD(void, placeTemp,
        (std::vector<std::unique_ptr<Tile> >& tiles, std::vector<Placement>& placements, unsigned char selection_mask),
        (override));
    MOCK_METHOD(void, getPlacements, (std::vector<Placement>& placements), (const, override));
    MOCK_METHOD(void, getOccupied, (std::vector<Placement>& placements), (const, override));
    MOCK_METHOD(void, acceptPlacements, (), (override));
    MOCK_METHOD(bool, areCoordsValid, (const Coords& coords), (const, override));
    MOCK_METHOD(bool, isSquareFree, (const Coords& coords), (const, override));
    MOCK_METHOD(bool, getTileLetterLowercase, (const Coords& coords, LetterLowercase& letter), (const, override));
    MOCK_METHOD(bool, getTileBaseScore, (const Coords& coords, int& score), (const, override));
    MOCK_METHOD(std::optional<const SquareDefinition>, getSquareDefinition, (const Coords& coords), (const, override));
    MOCK_METHOD(void, returnPlacements, (std::vector<std::unique_ptr<Tile>>& tiles), (override));
    MOCK_METHOD(void, returnPlacements,
        (std::vector<std::unique_ptr<Tile>>& tiles, const std::vector<Placement>& placements, unsigned char
            selection_mask), (override));
    MOCK_METHOD(void, assumeLetter, (const Coords& coords, const Letter& letter), (override));
};

#endif //MOCKS_H
