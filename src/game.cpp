//
// Created by Neven Boric on 4/19/25.
//

#include "game.h"

#include <iostream>

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
        players_.push_back(std::make_unique<Player>());
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
}

void Game::handleClick(const sf::Vector2i pos, const ClickEvent event)
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
        if (!is_exchanging_ && board_.shouldHandleClick(pos))
        {
            if (board_.canTakeTile(pos))
            {
                if (std::unique_ptr<Tile> selected;
                    (selected = players_[current_player_]->getSelectedTile()) != nullptr)
                {
                    board_.placeTemp(pos, selected);
                }
            }
            return;
        }
        players_[current_player_]->handleClick(pos, is_exchanging_);
    }
}

void Game::nextPlayer()
{
    current_player_ = (current_player_ + 1) % players_.size();
}
