#include "Tile.h"

Tile::Tile()
{
    tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    tile.setFillColor(sf::Color::Black);
    tile.setOutlineColor(sf::Color::White);
    tile.setOutlineThickness(1.0);
}
void Tile::drawTiles(sf::RenderWindow& window)
{

    for (int rows = 0; rows < WINDOW_HEIGHT; rows += TILE_SIZE)
    {
        for (int columns = 0; columns < WINDOW_WIDTH; columns += TILE_SIZE)
        {
            tile.setPosition(sf::Vector2f(float(columns), float(rows)));
            window.draw(tile);
        }
    }
}