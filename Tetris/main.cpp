#include <SFML/Graphics.hpp>
#include "Figures.h"
#include <iostream>
const float MOVE_INTERVAL = 1.0f;
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");

    sf::Clock moveClock; 
    float elapsedSeconds = 0.0f; 
    Tile tile;
    std::unique_ptr<Figures> tetromino = std::make_unique<Figures>(Tetrominos[(rand() % Tetrominos.size())]);



    while (window.isOpen())
    {
        std::vector<std::vector<sf::Color>> colorMap = tile.getColorMap();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                // Handle keyboard inputs
                if (event.key.code == sf::Keyboard::Left)
                {
                    // Move tetromino left
                    tetromino->moveLeft(colorMap);
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    // Move tetromino right
                    tetromino->moveRight(colorMap);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    // Move tetromino down (faster)
                    tetromino->moveDown(colorMap);
                }
                // You can add more controls here if needed
            }
        }

        window.clear();

        tile.drawTiles(window);

        float deltaTime = moveClock.restart().asSeconds();
        elapsedSeconds += deltaTime;

        if (elapsedSeconds >= MOVE_INTERVAL)
        {
            if (!tetromino->checkColisions(colorMap)) {

                std::vector<std::vector<int>> shape = tetromino->getShape();
                int posX = tetromino->getPosX();
                int posY = tetromino->getPosY();
                sf::Color color = tetromino->getColor();
                tile.updateMap(shape, posX, posY, color);

                tetromino = std::make_unique<Figures>(Tetrominos[(rand() % Tetrominos.size())]);
            }
            else { tetromino->moveFigures(); }

            elapsedSeconds -= MOVE_INTERVAL; 
        }
 
        tetromino->drawFigures(window);
        
        window.display();
    }

    window.~RenderWindow();

    return 0;
}