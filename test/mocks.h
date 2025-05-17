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
    MOCK_METHOD(void, getPlacements, (std::vector<Placement>& placements), (const, override));
    MOCK_METHOD(void, acceptPlacements, (), (override));
    MOCK_METHOD(bool, isSquareFree, (const Coords& coords), (const, override));
    MOCK_METHOD(bool, getTileLetter, (const Coords& coords, std::wstring& letter), (const, override));
    MOCK_METHOD(bool, getTileBaseScore, (const Coords& coords, int& score), (const, override));
    MOCK_METHOD(std::optional<const SquareDefinition>, getSquareDefinition, (const Coords& coords), (const, override));
    MOCK_METHOD(void, returnPlacements, (std::vector<std::unique_ptr<Tile>>& tiles), (override));
    MOCK_METHOD(void, assumeLetter, (const Coords& coords, const std::wstring& letter), (override));
};

#endif //MOCKS_H
