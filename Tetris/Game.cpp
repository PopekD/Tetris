#include "Game.h"
#include <iostream>

#define TILE_SIZE 40.0
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800

int Game::score = 0;

Game::Game() 
{
	if (!font.loadFromFile("bin/x420/NoWW/Tetris.ttf")) {
		std::cout << "Failed";
	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(WINDOW_WIDTH + 50, WINDOW_HEIGHT / 2);

	if (!imageTexture0.loadFromFile("bin/x420/NoWW/0points.png")) {
		std::cout << "Failed to load 0 points image." << std::endl;
	}
	if (!imageTexture25.loadFromFile("bin/x420/NoWW/25points.jpg")) {
		std::cout << "Failed to load 25 points image." << std::endl;
	}
	if (!imageTexture50.loadFromFile("bin/x420/NoWW/50points.jpg")) {
		std::cout << "Failed to load 50 points image." << std::endl;
	}
	if (!imageTexture75.loadFromFile("bin/x420/NoWW/75points.jpg")) {
		std::cout << "Failed to load 75 points image." << std::endl;
	}
	if (!imageTexture100.loadFromFile("bin/x420/NoWW/100points.jpg")) {
		std::cout << "Failed to load 100 points image." << std::endl;
	}
	if (!imageTexture150.loadFromFile("bin/x420/NoWW/150points.jpg")) {
		std::cout << "Failed to load 150 points image." << std::endl;
	}
	if (!imageTexture200.loadFromFile("bin/x420/NoWW/200points.jpg")) {
		std::cout << "Failed to load 200 points image." << std::endl;
	}
	if (!imageTexture300.loadFromFile("bin/x420/NoWW/300points.jpg")) {
		std::cout << "Failed to load 300 points image." << std::endl;
	}


	imageSprite.setPosition(sf::Vector2f(650, 50));

}
void Game::DisplayScore(sf::RenderWindow& window)
{
	scoreText.setString("Score: " + std::to_string(score));
	window.draw(scoreText);
}
void Game::setScore(int numClearedRows)
{
	score+= numClearedRows;
	return;
}
void Game::restartScore()
{
	score = 0;
}
void Game::drawPic(sf::RenderWindow& window)
{
	if (score >= 0 && score < 25)
	{
		imageSprite.setTexture(imageTexture0);
	}
	else if (score >= 25 && score < 50)
	{
		imageSprite.setTexture(imageTexture25);
	}
	else if (score >= 50 && score < 75)
	{
		imageSprite.setTexture(imageTexture50);
	}
	else if (score >= 75 && score < 100)
	{
		imageSprite.setTexture(imageTexture75);
	}
	else if (score >= 100 && score < 150)
	{
		imageSprite.setTexture(imageTexture100);
	}
	else if (score >= 150 && score < 200)
	{
		imageSprite.setTexture(imageTexture150);
	}
	else if (score >= 200 && score < 300)
	{
		imageSprite.setTexture(imageTexture200);
	}
	else
	{
		imageSprite.setTexture(imageTexture300);
	}

	window.draw(imageSprite);
}

void Game::refillTetrominoQueue()
{
	tetrominoQueue.push(rand() % 4);
	tetrominoQueue.push(rand() % 4 + 4);
	tetrominoQueue.push(rand() % 4 + 8);
	tetrominoQueue.push(12);
	tetrominoQueue.push(rand() % 4 + 16);
	tetrominoQueue.push(rand() % 4 + 20);
	tetrominoQueue.push(rand() % 4 + 24);

	std::vector<int> tetrominoVector;
	while (!tetrominoQueue.empty()) {
		tetrominoVector.push_back(tetrominoQueue.front());
		tetrominoQueue.pop();
	}
	std::shuffle(tetrominoVector.begin(), tetrominoVector.end(), std::default_random_engine(std::random_device()()));
	for (const auto& tetromino : tetrominoVector) {
		tetrominoQueue.push(tetromino);
	}

}