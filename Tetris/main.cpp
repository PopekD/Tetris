#include <SFML/Graphics.hpp>
#include "Figures.h"
#include <iostream>
#include <cstdio>

float MOVE_INTERVAL = 1.0f;
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH + 500, WINDOW_HEIGHT), "Tetris", sf::Style::Titlebar);

    sf::Clock moveClock; 
    float elapsedSeconds = 0.0f; 
    Tile tile;
    Game game;
    int nextTetromino = 0;
    bool isPaused = false;

    if (game.tetrominoQueue.empty())
    {
        game.refillTetrominoQueue();
        nextTetromino = game.tetrominoQueue.front();
        game.tetrominoQueue.pop();
    }

    std::unique_ptr<Figures> tetromino = std::make_unique<Figures>(Tetrominos[nextTetromino]);
    bool isGameOver = false;

    sf::SoundBuffer buffer;
    sf::Sound sound;
    if (buffer.loadFromFile("bin/x420/NoWW/tetris.mp3"))
    {
        float pitch = 1.0f;
        sound.setBuffer(buffer);

        sound.setPitch(pitch);
        sound.setLoop(true);
        sound.play();
    }
    sf::SoundBuffer losebuffer;
    sf::Sound losesound;

    if (losebuffer.loadFromFile("bin/x420/NoWW/lose.wav"))
    {
        float pitch = 1.0f;
        losesound.setBuffer(losebuffer);
        losesound.setPitch(pitch);
    }
    nextTetromino = game.tetrominoQueue.front();
    game.tetrominoQueue.pop();
    int pos = 0;
    while (!isGameOver)
    {
        std::vector<std::vector<sf::Color>> colorMap = tile.getColorMap();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case(sf::Keyboard::Left):
                        tetromino->moveLeft(colorMap);
                        break;
                    case(sf::Keyboard::Right):
                        tetromino->moveRight(colorMap);
                        break;
                    case(sf::Keyboard::Down):
                        tetromino->moveDown(colorMap);
                        break;
                    case(sf::Keyboard::S):
                        tetromino->rotate(colorMap, event.key.code);
                        break;
                    case(sf::Keyboard::D):
                        tetromino->rotate(colorMap, event.key.code);
                        break;
                    case(sf::Keyboard::P):
                        isPaused = !isPaused;
                        break;
                    case(sf::Keyboard::LControl):
                        tetromino->swapTetrominos(tetromino, game.tetrominoQueue);
                        break;
                    case(sf::Keyboard::Space):
                        tetromino->isSpacePressed(true);
                        pos = tetromino->getGhostPosition();
                        tetromino->setPosY(pos);          
                        break;
                }
            }
        }
        if (!isPaused)
        {
            window.clear();
            tile.drawTiles(window, sound);
            float deltaTime = moveClock.restart().asSeconds();
            elapsedSeconds += deltaTime;


            if (elapsedSeconds >= MOVE_INTERVAL)
            {
                tetromino->isSpacePressed(false);
                if (!tetromino->checkCollisions(colorMap)) {

                    if (!tetromino->checkCollisionsAtSpawn(colorMap)) {
                        sound.setLoop(false);
                        sound.stop();
                        losesound.play();
                        tile.setPitch();
                        isGameOver = true;
                        break;
                    }
                    
                    std::vector<std::vector<int>> shape = tetromino->getShape();
                    int posX = tetromino->getPosX();
                    int posY = tetromino->getPosY();
                    sf::Color color = tetromino->getColor();
                    tile.updateMap(shape, posX, posY, color);

                    tetromino = std::make_unique<Figures>(Tetrominos[nextTetromino]);
                    Figures::didCtrlClick = false;

                    MOVE_INTERVAL = tile.getSpeed();

                    nextTetromino = game.tetrominoQueue.front();
                    game.tetrominoQueue.pop();

                    if (game.tetrominoQueue.empty())
                    {
                        game.refillTetrominoQueue();
                    }
                }
                else { tetromino->moveFigures(); }

                elapsedSeconds -= MOVE_INTERVAL;
            }
            tetromino->isSpacePressed(false);
            tetromino->drawNext(window, nextTetromino);
            game.drawPic(window);
            game.DisplayScore(window);
            tetromino->drawFigures(window);
            tetromino->drawGhost(window,colorMap);
            tetromino->drawInventory(window);
            window.display();
        }
        else
        {
            sound.pause();
            while (isPaused) 
            {
                sf::Event pauseEvent;
                while (window.pollEvent(pauseEvent))
                {
                    if (pauseEvent.type == sf::Event::KeyPressed && pauseEvent.key.code == sf::Keyboard::P)
                    {
                        sound.play();
                        isPaused = !isPaused; 
                    }
                }
            }
            moveClock.restart();
        }

    }

    while (isGameOver)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            window.close();
            isGameOver = false;
            game.restartScore();
            main();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            break;
        }
       
    }
    window.~RenderWindow();

    return 0;
}