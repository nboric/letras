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
public:
    virtual ~Board() = default;

    virtual void draw(sf::RenderWindow& window, const sf::Font& font) const = 0;
    [[nodiscard]] virtual std::optional<Coords> shouldHandleClick(sf::Vector2i pos) const = 0;
    [[nodiscard]] virtual bool canTakeTile(sf::Vector2i pos) const = 0;
    virtual void placeTemp(sf::Vector2i pos, std::unique_ptr<Tile>& tile) = 0;
    virtual void getPlacements(std::vector<Placement>& placements) const = 0;
    virtual void acceptPlacements() = 0;
    [[nodiscard]] virtual bool isSquareFree(const Coords& coords) const = 0;
    virtual bool getTileLetter(const Coords& coords, std::wstring& letter) const = 0;
    virtual bool getTileBaseScore(const Coords& coords, int& score) const = 0;
    [[nodiscard]] virtual std::optional<const SquareDefinition> getSquareDefinition(const Coords& coords) const = 0;
    virtual void returnPlacements(std::vector<std::unique_ptr<Tile>>& tiles) = 0;
    virtual void assumeLetter(const Coords& coords, const std::wstring& letter) = 0;
};

class BoardImpl final : public Board
{
    static constexpr int SIZE{ 15 };
    static constexpr int BORDER{ 20 };

    static const std::map<Coords, SquareDefinition> premium_squares_;

    std::vector<std::vector<Square> > squares_;

    static bool getSquareCoords(sf::Vector2i pos, Coords& coords);

public:
    BoardImpl();

    static constexpr Coords center_coords_{ SIZE / 2, SIZE / 2 };

    void draw(sf::RenderWindow& window, const sf::Font& font) const override;
    [[nodiscard]] std::optional<Coords> shouldHandleClick(sf::Vector2i pos) const override;
    [[nodiscard]] bool canTakeTile(sf::Vector2i pos) const override;
    void placeTemp(sf::Vector2i pos, std::unique_ptr<Tile>& tile) override;
    void getPlacements(std::vector<Placement>& placements) const override;
    void acceptPlacements() override;
    [[nodiscard]] bool isSquareFree(const Coords& coords) const override;
    bool getTileLetter(const Coords& coords, std::wstring& letter) const override;
    bool getTileBaseScore(const Coords& coords, int& score) const override;
    [[nodiscard]] std::optional<const SquareDefinition> getSquareDefinition(const Coords& coords) const override;
    void returnPlacements(std::vector<std::unique_ptr<Tile>>& tiles) override;
    void assumeLetter(const Coords& coords, const std::wstring& letter) override;
};

#endif //BOARD_H
