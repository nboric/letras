//
// Created by Neven Boric on 4/19/25.
//

#include "game.h"

#include <iostream>

#include "human_player.h"
#include "play_rules/play.h"

Game::Game(const int n_players)
    : play_button_("JUGAR"),
      cancel_button_("CANCELAR"),
      exchange_start_button_("CAMBIAR"),
      dict_("res/dict/fise-2.txt"),
      play_builder_(dict_)
{
    if (n_players < MIN_PLAYERS || n_players > MAX_PLAYERS)
    {
        return;
    }
    for (int i = 0; i < n_players; i++)
    {
        players_.push_back(std::make_unique<HumanPlayer>());
    }
}

void Game::replenish_all()
{
    for (const auto& player : players_)
    {
        player->replenish(bag_);
    }
}

void Game::draw(sf::RenderWindow& window, const sf::Font& font)
{
    board_.draw(window, font);
    play_button_.draw(window, font, { 800.f, 600.f }, false);
    cancel_button_.draw(window, font, { 950.f, 600.f }, false);
    exchange_start_button_.draw(window, font, { 800.f, 680.f }, is_exchanging_);
    bag_.draw(window, font, { 950.f, 680.f });
    for (int i = 0; i < players_.size(); i++)
    {
        const auto& player = players_[i];
        player->draw(window, font, i == current_player_, { 800.f, static_cast<float>(100 + 140 * i) });
    }
    if (is_picking_wildcard_)
    {
        wildcard_picker_.draw(window, font, { 400.f, 300.f });
    }
}

void Game::handleClick(const sf::Vector2i pos, const ClickEvent event)
{
    if (players_[current_player_]->isInteractive())
    {
        if (!is_exchanging_ && play_button_.handleClick(pos, event))
        {
            if (event == CLICK_END)
            {
                Play play(board_);
                std::string rule, reason;
                if (!play_builder_.build(play, board_, rule, reason))
                {
                    std::cout << "Failed rule " << rule << ", reason: " << reason << std::endl;
                }
                else
                {
                    board_.acceptPlacements();
                    players_[current_player_]->addScore(play.score);
                    players_[current_player_]->replenish(bag_);
                    nextPlayer();
                }
            }
        }
        if (exchange_start_button_.handleClick(pos, event))
        {
            if (event == CLICK_END)
            {
                if (is_exchanging_)
                {
                    players_[current_player_]->exchange(bag_);
                    nextPlayer();
                }
                is_exchanging_ = !is_exchanging_;
            }
        }
        if (cancel_button_.handleClick(pos, event))
        {
            if (event == CLICK_END)
            {
                if (is_exchanging_)
                {
                    is_exchanging_ = false;
                    players_[current_player_]->unselectAll();
                }
                else
                {
                    std::vector<std::unique_ptr<Tile> > tiles;
                    board_.returnPlacements(tiles);
                    players_[current_player_]->takeAll(tiles);
                }
            }
        }
        if (event == CLICK_START)
        {
            if (is_picking_wildcard_ && wildcard_picker_.handleClick(pos, event))
            {
                if (const auto letter = wildcard_picker_.handleClick(pos, event); letter.has_value())
                {
                    board_.assumeLetter(pending_wildcard_.value(), letter.value());
                    pending_wildcard_.reset();
                    is_picking_wildcard_ = false;
                    return;
                }
            }
            if (!is_exchanging_)
            {
                if (const auto coords = board_.shouldHandleClick(pos); coords.has_value())
                {
                    if (board_.canTakeTile(pos))
                    {
                        if (std::unique_ptr<Tile> selected;
                            (selected = players_[current_player_]->getSelectedTile()) != nullptr)
                        {
                            const bool is_wildcard = selected->isWildcard();
                            board_.placeTemp(pos, selected);
                            if (is_wildcard)
                            {
                                pending_wildcard_ = coords;
                                is_picking_wildcard_ = true;
                            }
                        }
                    }
                    return;
                }
            }
            players_[current_player_]->handleClick(pos, is_exchanging_);
        }
    }
    else
    {
        switch (players_[current_player_]->getAction(board_))
        {
        default: ;
        }
    }
}

void Game::nextPlayer()
{
    current_player_ = (current_player_ + 1) % players_.size();
    is_exchanging_ = is_picking_wildcard_ = false;
    pending_wildcard_.reset();
}
