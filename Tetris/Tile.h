#include <SFML/Graphics.hpp>

#define TILE_SIZE 40.0
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800

class Tile {

private:
	sf::RectangleShape tile;
public:
	Tile();
	void drawTiles(sf::RenderWindow& window);
};