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
#include "wildcard_picker.h"
#include "play_rules/play_builder.h"
#include "SFML/Graphics/Font.hpp"

class Game
{
    static constexpr int MIN_PLAYERS{ 2 };
    static constexpr int MAX_PLAYERS{ 4 };
    std::vector<std::unique_ptr<Player> > players_;

    size_t current_player_{ 0 };
    bool is_exchanging_{ false };
    bool is_picking_wildcard_{ false };
    std::optional<Coords> pending_wildcard_;

    BoardImpl board_;
    Bag bag_;
    Button play_button_;
    Button cancel_button_;
    Button exchange_start_button_;

    std::shared_ptr<const Dict> dict_;

    PlayBuilder play_builder_;

    WildcardPicker wildcard_picker_;

public:
    explicit Game(int n_players);
    void replenish_all();

    void draw(sf::RenderWindow& window, const sf::Font& font);
    void nextPlayer();
    void handleClick(sf::Vector2i pos, ClickEvent event);
};

#endif //GAME_H
