#include <SFML/Graphics.hpp>

#include "game.h"

int main()
{
    Game game{2};
    game.replenish_all();

    sf::Font font("/System/Library/Fonts/SFCompact.ttf");

    auto window = sf::RenderWindow(sf::VideoMode({1080u, 1080u}), "Letras");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        game.draw(window, font);
        window.display();
    }

    return 0;
}
