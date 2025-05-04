//
// Created by Neven Boric on 4/19/25.
//

#include "game.h"

Game::Game(const int n_players): dict_("res/dict/fise-2.txt")
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

void Game::draw(sf::RenderWindow& window, const sf::Font& font) const
{
    board_.draw(window);
    for (int i = 0; i < players_.size(); i++)
    {
        const auto& player = players_[i];
        player->draw(window, font, {800.f, 100.f + 80 * i});
    }
}
