#include <SFML/Graphics.hpp>

#include "game.h"

int main()
{
    Game game{ 2 };
    game.replenish_all();

    const sf::Font font(FONT_PATH);

    auto window = sf::RenderWindow(sf::VideoMode({ 1200u, 800u }), "Letras");

    while (window.isOpen())
    {
        window.handleEvents(
            [&](const sf::Event::Closed&)
            {
                window.close();
            },
            [&](const sf::Event::MouseButtonPressed& mouse_event)
            {
                if (mouse_event.button == sf::Mouse::Button::Left)
                {
                    game.handleClick(mouse_event.position);
                }
            }
        );

        window.clear(sf::Color::White);
        game.draw(window, font);
        window.display();
    }

    return 0;
}
