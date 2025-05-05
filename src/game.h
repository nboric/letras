//
// Created by Neven Boric on 4/19/25.
//

#ifndef GAME_H
#define GAME_H
#include "bag.h"
#include "board.h"
#include "button.h"
#include "dict.h"
#include "player.h"
#include "restrictions/restriction.h"
#include "SFML/Graphics/Font.hpp"

class Game
{
    static constexpr int MIN_PLAYERS{ 2 };
    static constexpr int MAX_PLAYERS{ 4 };
    std::vector<std::unique_ptr<Player> > players_;

    Board board_;
    Bag bag_;
    Button play_button_;
    Button cancel_button_;

    Dict dict_;

    std::vector<std::unique_ptr<Restriction> > restrictions_;

public:
    explicit Game(int n_players);
    void replenish_all();

    void draw(sf::RenderWindow& window, const sf::Font& font);
    void handleClick(sf::Vector2i pos);
};

#endif //GAME_H
