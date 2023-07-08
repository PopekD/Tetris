#include "Figures.h"
#include <iostream>

bool Figures::inventoryEmpty = true;
std::unique_ptr<Figures> Figures::inventoryTetromino = std::make_unique<Figures>(Tetrominos[0]);
bool Figures::didCtrlClick = false;

void Figures::drawFigures(sf::RenderWindow& window)
{
	tileShape.setFillColor(getColor());
	tileShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	tileShape.setOutlineColor(sf::Color::Black);
	tileShape.setOutlineThickness(2);

	std::vector<std::vector<int>> shape = getShape();

	minX = std::numeric_limits<int>::max();
	maxX = std::numeric_limits<int>::min();
	maxY = std::numeric_limits<int>::min();


	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[i].size(); j++) {
			if (shape[i][j] == 1)
			{
				tileShape.setPosition(float(posX + i * TILE_SIZE), float(posY + (j * TILE_SIZE)));
				window.draw(tileShape);

				minX = std::min(minX, int(posX + i * TILE_SIZE));
				maxX = std::max(maxX, int(posX + i * TILE_SIZE));
				maxY = std::max(maxY, int(posY + j * TILE_SIZE));
				minY = std::min(minY, int(posY + j * TILE_SIZE));
			}
		}
	}

}
void Figures::isSpacePressed(bool KeyPressed)
{
	isSpaceKeyPressed = KeyPressed;
}
void Figures::moveFigures() {
	if (!isSpaceKeyPressed)
	{
		setPosY(int(posY += TILE_SIZE));
	}
}


bool Figures::checkCollisions(std::vector<std::vector<sf::Color>>& colorMap)
{

	if (maxY + TILE_SIZE > bottomBoundary)
	{
		return false;
	}

	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if (shape[i][j] == 1)
			{
				int mapX = (posX / TILE_SIZE) + i;
				int mapY = (posY / TILE_SIZE) + j;
				if (mapX >= 0 && mapX < colorMap[0].size() && mapY >= 0 && mapY < colorMap.size())
				{

					if (colorMap[mapY+1][mapX] != sf::Color::Black)
					{
						return false;
					}
				}

			}
		}
	}
	return true;
}
bool Figures::checkCollisionsAtSpawn(std::vector<std::vector<sf::Color>>& colorMap)
{
	int InitposX = (WINDOW_WIDTH / 2) - TILE_SIZE;
	int InitposY = 0;

	if ( posX == InitposX && InitposY == posY) {
		return false;
	}

	return true;
}

void Figures::moveLeft(std::vector<std::vector<sf::Color>>& colorMap)
{
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if (shape[i][j] == 1)
			{
				int tileX = (posX + i * TILE_SIZE) / TILE_SIZE;
				int tileY = (posY + j * TILE_SIZE) / TILE_SIZE;

				if (tileX == 0)
				{
					return;
				}

				if (colorMap[tileY][tileX - 1] != sf::Color::Black)
				{
					return;
				}
			}
		}
	}

	setPosX(int(posX - TILE_SIZE));
}
void Figures::moveRight(std::vector<std::vector<sf::Color>>& colorMap)
{
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if (shape[i][j] == 1)
			{
				int tileX = (posX + i * TILE_SIZE) / TILE_SIZE;
				int tileY = (posY + j * TILE_SIZE) / TILE_SIZE;


				if (tileX >= (WINDOW_WIDTH / TILE_SIZE) - 1)
				{
					return;
				}

				if (colorMap[tileY][tileX + 1] != sf::Color::Black)
				{
					return;
				}
			}
		}
	}
	setPosX(int(posX + TILE_SIZE));
}
void Figures::moveDown(std::vector<std::vector<sf::Color>>& colorMap)
{
	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if (shape[i][j] == 1)
			{
				int tileX = (posX + i * TILE_SIZE) / TILE_SIZE;
				int tileY = (posY + j * TILE_SIZE) / TILE_SIZE;


				if (tileY == (WINDOW_HEIGHT / TILE_SIZE) - 1)
				{
					return;
				}

				if (colorMap[tileY + 1][tileX] != sf::Color::Black)
				{
					return;
				}
			}
		}
	}

	setPosY(int(posY + TILE_SIZE));
}

void Figures::rotate(std::vector<std::vector<sf::Color>>& colorMap, sf::Keyboard::Key key)
{

	std::vector<std::vector<int>> rotatedShape = shape;


	int nextRotationState = rotationState;

	switch (key)
	{
	case sf::Keyboard::S:
		nextRotationState = (++rotationState) % 4;
		break;
	case sf::Keyboard::D:
		nextRotationState = (--rotationState + 4) % 4;
		break;
	}


	std::vector<std::vector<int>> nextRotatedShape;

	for (const Figures& figure : Tetrominos)
	{
		if (figure.type == type && figure.rotationState == nextRotationState)
		{
			nextRotatedShape = figure.shape;
			break;
		}
	}

	for (int i = 0; i < nextRotatedShape.size(); i++)
	{
		for (int j = 0; j < nextRotatedShape[i].size(); j++)
		{
			if (nextRotatedShape[i][j] == 1)
			{
				int mapX = (posX / TILE_SIZE) + i;
				int mapY = (posY / TILE_SIZE) + j;
				maxY = std::max(maxY, int(posY + j * TILE_SIZE));
				if (mapX >= 0 && mapX < (WINDOW_WIDTH / TILE_SIZE) && mapY >= 0 && mapY < colorMap.size())
				{
					if (colorMap[mapY][mapX] != sf::Color::Black)
					{
						return;
					}
				}
				else
				{
					return;
				}

			}
		}
	}
	if (maxY > bottomBoundary)
	{
		return;
	}


	shape = nextRotatedShape;
	rotationState = nextRotationState;
}


void Figures::drawNext(sf::RenderWindow& window, int next)
{
	Figures p = Tetrominos[next];
	std::vector<std::vector<int>> shape = p.getShape();
	
	nextShape.setFillColor(sf::Color::White);
	nextShape.setSize(sf::Vector2f(NEXTSIZE, NEXTSIZE));
	nextShape.setOutlineColor(sf::Color::Blue);
	nextShape.setOutlineThickness(2);

	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[i].size(); j++) {
			if (shape[i][j] == 1)
			{
				nextShape.setPosition(float(WINDOW_WIDTH + 100 + i * NEXTSIZE), float(100 + (j * NEXTSIZE)));
				window.draw(nextShape);
			}
		}
	}
}
bool Figures::isValidPosition(int posY, const std::vector<std::vector<sf::Color>>& colormap)
{

	for (int i = 0; i < shape.size(); i++)
	{
		for (int j = 0; j < shape[i].size(); j++)
		{
			if (shape[i][j] == 1)
			{
				int mapX = (posX / TILE_SIZE) + i;
				int mapY =  posY + j;

				if (mapX >= 0 && mapX < colormap[0].size() && mapY >= 0 && mapY <= colormap.size())
				{
					if (mapY < 20 && colormap[mapY][mapX] != sf::Color::Black)
					{
						
						return true;
					}
					else if (mapY == 20)
					{
						return true;
					}
				}

			}
		}
	}
	return false;
}


void Figures::drawGhost(sf::RenderWindow& window, std::vector<std::vector<sf::Color>>& colormap)
	{
		ghostShape.setFillColor(sf::Color(0, 0, 0, 0));
		ghostShape.setOutlineThickness(2.0f);
		ghostShape.setOutlineColor(sf::Color(255, 130, 255));
		ghostShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));

		int Y = posY / TILE_SIZE;

		while (Y <= int((WINDOW_HEIGHT / TILE_SIZE)))
		{
			if (isValidPosition(Y, colormap))
			{
				ghostPosition = Y;
				for (int i = 0; i < shape.size(); i++)
				{
					for (int j = 0; j < shape[i].size(); j++)
					{
						if (shape[i][j] == 1)
						{
							int ghostP = (Y - 1) - (shape[0].size() - shape[0].size() - j);
							ghostShape.setPosition(sf::Vector2f(float(posX + i * TILE_SIZE), float(ghostP * TILE_SIZE)));
							window.draw(ghostShape);

							ghostPosition = std::min(ghostPosition, int(ghostP));
						}
					}
				}
				return;
			}
			else
			{
				Y++;
			}
		}
	}

void Figures::swapTetrominos(std::unique_ptr<Figures>& tetromino, std::queue<int>& tetrominoQueue)
{
	if (inventoryEmpty)
	{
		int nextTetromino = tetrominoQueue.front();
		tetrominoQueue.pop();

		if (tetrominoQueue.empty())
		{
			Game().refillTetrominoQueue();
		}

		inventoryTetromino = std::move(tetromino);
		tetromino = std::make_unique<Figures>(Tetrominos[nextTetromino]);
		inventoryEmpty = false;
		didCtrlClick = true;
		return;
	}
	else if (!didCtrlClick)
	{
		
		didCtrlClick = true;
		std::swap(tetromino, inventoryTetromino);
		setPosX((WINDOW_WIDTH / 2) - TILE_SIZE);
		setPosY(0);
	}

}
void Figures::drawInventory(sf::RenderWindow& window)
{
	if (!inventoryEmpty)
	{
		std::vector<std::vector<int>> shape = inventoryTetromino->getShape();

		inventoryShape.setFillColor(sf::Color::Magenta);
		inventoryShape.setSize(sf::Vector2f(NEXTSIZE, NEXTSIZE));
		inventoryShape.setOutlineColor(sf::Color::White);
		inventoryShape.setOutlineThickness(2);

		for (int i = 0; i < shape.size(); i++) {
			for (int j = 0; j < shape[i].size(); j++) {
				if (shape[i][j] == 1)
				{
					inventoryShape.setPosition(float(WINDOW_WIDTH + 100 + i * NEXTSIZE), float(250 + (j * NEXTSIZE)));
					window.draw(inventoryShape);
				}
			}
		}
	}
}

int Figures::getGhostPosition()
{
	return ghostPosition * TILE_SIZE;
}


void Figures::setPosY(int posY)
{
	this->posY = posY;
}

void Figures::setPosX(int posX)
{
	this->posX = posX;
}
int Figures::getPosY()
{
	return posY;
}

int Figures::getPosX()
{
	return posX;
}