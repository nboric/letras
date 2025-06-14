//
// Created by Neven Boric on 4/19/25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "action.h"
#include "board.h"
#include "bag.h"
#include "score.h"
#include "tile.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Player
{
protected:
    static constexpr int MAX_TILES{ 7 };
    std::vector<std::unique_ptr<Tile> > tiles_;
    Score score_;

public:
    virtual ~Player() = default;
    virtual void replenish(Bag& bag);
    virtual void draw(sf::RenderWindow& window, const sf::Font& font, bool is_active, sf::Vector2f base_pos) const = 0;
    virtual void handleClick(sf::Vector2i pos, bool is_exchanging) const = 0;
    virtual std::unique_ptr<Tile> getSelectedTile() = 0;
    virtual void addScore(int score);
    virtual void takeAll(std::vector<std::unique_ptr<Tile> >& tiles);
    virtual void unselectAll() const = 0;
    virtual void exchange(Bag& bag) = 0;
    [[nodiscard]] Action getAction(const Board& board) const { return NONE; }
    [[nodiscard]] virtual bool isInteractive() const = 0;
};

#endif //PLAYER_H
