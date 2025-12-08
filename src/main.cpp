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
        if (const std::optional<sf::Event> event = window.waitEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* button_released_event = event->getIf<sf::Event::MouseButtonReleased>())
            {
                game.handleClick(button_released_event->position, CLICK_END);
            }
        }
        window.clear(sf::Color::White);
        game.draw(window, font);
        window.display();
    }

    return 0;
}
