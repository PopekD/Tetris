#include <SFML/Graphics.hpp>
#include "Game.h"
#define TILE_SIZE 40.0
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800


class Tile: private Game{

protected:
	sf::RectangleShape tile;
	sf::RectangleShape lastLanded;
	std::vector<std::vector<sf::Color>> colorMap;
	float speed;
	float pitch = 1.0;
public:
	Tile();
	void updateMap(std::vector<std::vector<int>>& shape, int posX, int posY, sf::Color color);
	void drawTiles(sf::RenderWindow& window, sf::Sound& sound);
	void checkMap();
	float getSpeed();
	std::vector<std::vector<sf::Color>> getColorMap();
	void setPitch();
};