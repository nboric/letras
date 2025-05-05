//
// Created by Neven Boric on 4/19/25.
//

#include "game.h"

#include <iostream>

#include "restrictions/contiguous.h"
#include "restrictions/dict_check.h"

Game::Game(const int n_players)
    : play_button_("JUGAR"), cancel_button_("CANCELAR"), dict_("res/dict/fise-2.txt")
{
    if (n_players < MIN_PLAYERS || n_players > MAX_PLAYERS)
    {
        return;
    }
    for (int i = 0; i < n_players; i++)
    {
        players_.push_back(std::make_unique<Player>());
    }
    restrictions_.push_back(std::make_unique<Contiguous>());
    restrictions_.push_back(std::make_unique<DictCheck>());
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
    play_button_.draw(window, font, { 800.f, 600.f });
    cancel_button_.draw(window, font, { 950.f, 600.f });
    for (int i = 0; i < players_.size(); i++)
    {
        const auto& player = players_[i];
        player->draw(window, font, { 800.f, static_cast<float>(100 + 80 * i) });
    }
}

void Game::handleClick(const sf::Vector2i pos)
{
    if (play_button_.handleClick(pos))
    {
        std::vector<Placement> placements;
        board_.getPlacements(placements);
        std::string reason;
        for (const auto& restriction : restrictions_)
        {
            if (!restriction->isValid(placements, dict_, reason))
            {
                std::cout << "Failed restriction " << restriction->getName() << ", reason: " << reason << std::endl;
            }
        }
    }
    if (board_.shouldHandleClick(pos))
    {
        if (board_.canTakeTile(pos))
        {
            // TODO: only current player
            for (const auto& player : players_)
            {
                if (std::unique_ptr<Tile> selected; (selected = player->getSelectedTile()) != nullptr)
                {
                    board_.place(pos, selected);
                }
            }
        }
        return;
    }
    // TODO: only current player
    for (const auto& player : players_)
    {
        player->handleClick(pos);
    }
}
