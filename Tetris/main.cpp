#include <SFML/Graphics.hpp>
#include "Tile.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");
    Tile tile;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        tile.drawTiles(window);
        window.display();
    }

    window.~RenderWindow();

    return 0;
}