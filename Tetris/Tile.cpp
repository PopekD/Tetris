#include "Tile.h"
#include <iostream>
Tile::Tile()
{
    tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    tile.setOutlineColor(sf::Color(255,255,255,100));
    tile.setOutlineThickness(1);
    colorMap.resize(WINDOW_HEIGHT / TILE_SIZE, std::vector<sf::Color>(WINDOW_WIDTH / TILE_SIZE, sf::Color::Black));
}
void Tile::drawTiles(sf::RenderWindow& window)
{

    for (int rows = 0; rows < WINDOW_HEIGHT / TILE_SIZE; rows++)
    {
        for (int columns = 0; columns < WINDOW_WIDTH / TILE_SIZE; columns++)
        {
            tile.setPosition(sf::Vector2f(float(columns * TILE_SIZE), float(rows * TILE_SIZE)));
            tile.setFillColor(colorMap[rows][columns]);
            window.draw(tile);
        }
    }
}
void Tile::updateMap(std::vector<std::vector<int>>& shape, int posX, int posY, sf::Color color)
{
    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == 1) {
                int row = (posY + (j * TILE_SIZE)) / TILE_SIZE;
                int column = (posX + (i * TILE_SIZE)) / TILE_SIZE;
                colorMap[row][column] = color;
            }
        }
    }
}
std::vector<std::vector<sf::Color>> Tile::getColorMap(){
    return colorMap;
}
