#include <SFML/Graphics.hpp>

#define TILE_SIZE 40.0
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800

class Tile {

protected:
	sf::RectangleShape tile;
	sf::RectangleShape lastLanded;
	std::vector<std::vector<sf::Color>> colorMap;
public:
	Tile();
	void updateMap(std::vector<std::vector<int>>& shape, int posX, int posY, sf::Color color);
	void drawTiles(sf::RenderWindow& window);
	void checkMap();
	std::vector<std::vector<sf::Color>> getColorMap();
};