#include <SFML/Graphics.hpp>
#include "Tile.h"

enum class FiguresType
{
	I,
	L,
	O,
	S,
	T
};
enum class RotationState 
{ 
	Deg0, 
	Deg90, 
	Deg180, 
	Deg270 
};

class Figures
{
private:
	FiguresType type;
	std::vector<std::vector<int>> shape;
	sf::Color color;
	sf::RectangleShape tileShape;
	int minX;
	int maxX;
	int maxY;
	int minY;
	const int bottomBoundary = int(WINDOW_HEIGHT - TILE_SIZE);
	RotationState rotationState = RotationState::Deg0;
protected:
	int posX = (WINDOW_WIDTH / 2) - TILE_SIZE;
	int posY = 0;
public:
	Figures(FiguresType figureType, sf::Color figureColor, std::vector<std::vector<int>> figureShape, RotationState initialRotationState)
		: type(figureType), color(figureColor), shape(figureShape), rotationState(initialRotationState) {}
	FiguresType getType() const {
		return type;
	}
	sf::Color getColor() const {
		return color;
	}
	const std::vector<std::vector<int>>& getShape() const {
		return shape;
	}
	void drawFigures(sf::RenderWindow& window);
	void setPosX(int posX);
	int getPosX();
	void setPosY(int posY);
	int getPosY();
	void moveFigures();
	bool checkCollisions(std::vector<std::vector<sf::Color>>& colorMap);
	void moveLeft(std::vector<std::vector<sf::Color>>& colorMap);
	void moveRight(std::vector<std::vector<sf::Color>>& colorMap);
	void moveDown(std::vector<std::vector<sf::Color>>& colorMap);
	void rotate(std::vector<std::vector<sf::Color>>& colorMap);
};

const std::vector<Figures> Tetrominos = {
    Figures(FiguresType::I, sf::Color::Cyan, {
        { 1, 1, 1 }
    }, RotationState::Deg0),
    Figures(FiguresType::I, sf::Color::Cyan, {
        { 0, 1, 0},
        { 0, 1, 0 },
        { 0, 1, 0 }
    }, RotationState::Deg90),
    Figures(FiguresType::I, sf::Color::Cyan, {
        { 1, 1, 1 }
    }, RotationState::Deg180),
    Figures(FiguresType::I, sf::Color::Cyan, {
        { 0, 1, 0},
        { 0, 1, 0 },
        { 0, 1, 0 }
    }, RotationState::Deg270),

    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 0, 0, 1 },
        { 1, 1, 1 }
    }, RotationState::Deg0),
    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 1, 0 },
        { 1, 0 },
        { 1, 1 }
    }, RotationState::Deg90),
    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 1, 1, 1 },
        { 1, 0, 0 }
    }, RotationState::Deg180),
    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 1, 1 },
        { 0, 1 },
        { 0, 1 }
    }, RotationState::Deg270),

    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, RotationState::Deg0),
    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, RotationState::Deg90),
    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, RotationState::Deg180),
    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, RotationState::Deg270),

    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 0, 1, 0 },
        { 1, 1, 1 }
    }, RotationState::Deg0),
    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 1, 0 },
        { 1, 1 },
        { 1, 0 }
    }, RotationState::Deg90),
    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 1, 1, 1 },
        { 0, 1, 0 }
    }, RotationState::Deg180),
    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 0, 1 },
        { 1, 1 },
        { 0, 1 }
    }, RotationState::Deg270),
    Figures(FiguresType::S, sf::Color::Red, {
        { 0, 1, 1 },
        { 1, 1, 0 }
    }, RotationState::Deg0),
    Figures(FiguresType::S, sf::Color::Red, {
        { 1, 0 },
        { 1, 1 },
        { 0, 1 }
    }, RotationState::Deg90),
        Figures(FiguresType::S, sf::Color::Red, {
        { 1, 1, 0 },
        { 0, 1, 1 }
    }, RotationState::Deg180),
    Figures(FiguresType::S, sf::Color::Red, {
        { 0, 1 },
        { 1, 1 },
        { 1, 0 }
    }, RotationState::Deg270)
};


