#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <algorithm>
#include <random>

class Game {
private:
	static int score;
	sf::Text scoreText;
	sf::Font font;
	float time;
	sf::Texture imageTexture0;
	sf::Texture imageTexture25;
	sf::Texture imageTexture50;
	sf::Texture imageTexture75;
	sf::Texture imageTexture100;
	sf::Texture imageTexture150;
	sf::Texture imageTexture200;
	sf::Texture imageTexture300;
	sf::Sprite imageSprite;
	public: std::queue<int> tetrominoQueue;
public:
	Game();
	void setScore(int numClearedRows);
	int getScore();
	void DisplayScore(sf::RenderWindow& window);
	void restartScore();
	void drawPic(sf::RenderWindow& window);
	void refillTetrominoQueue();
};