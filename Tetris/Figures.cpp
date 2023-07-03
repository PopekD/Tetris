#include "Figures.h"
#include <iostream>

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
void Figures::moveFigures() {
	setPosY(int(posY += TILE_SIZE));
}

bool Figures::checkColisions(std::vector<std::vector<sf::Color>>& colorMap)
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