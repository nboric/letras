//
// Created by Neven Boric on 4/19/25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "bag.h"
#include "score.h"
#include "tile.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Player
{
    static constexpr int MAX_TILES{ 7 };
    std::vector<std::unique_ptr<Tile> > tiles_;
    Score score_;

    friend class PlayerTest;

public:
    Player();
    void replenish(Bag& bag);
    void draw(sf::RenderWindow& window, const sf::Font& font, bool is_active, sf::Vector2f base_pos) const;
    void handleClick(sf::Vector2i pos, bool is_exchanging) const;
    std::unique_ptr<Tile> getSelectedTile();
    void addScore(int score);
    void takeAll(std::vector<std::unique_ptr<Tile> >& tiles);
    void unselectAll() const;
    void exchange(Bag& bag);
};

#endif //PLAYER_H
