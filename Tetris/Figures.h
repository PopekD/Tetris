#include <SFML/Graphics.hpp>
#include "Tile.h"

#define NEXTSIZE 25.0

enum class FiguresType
{
	I,
	L,
	O,
	S,
	T,
    J,
    Z
};


class Figures
{
private:
	FiguresType type;
	std::vector<std::vector<int>> shape;
	sf::Color color;
	sf::RectangleShape tileShape;
    sf::RectangleShape nextShape;
    sf::RectangleShape ghostShape;
    sf::RectangleShape inventoryShape;
    static std::unique_ptr<Figures> inventoryTetromino;
	int minX;
	int maxX;
	int maxY;
	int minY;
    int ghostPosition;
    bool isSpaceKeyPressed;
    static bool inventoryEmpty;
	const int bottomBoundary = int(WINDOW_HEIGHT - TILE_SIZE);
    public: int rotationState = 0;
    static bool didCtrlClick;
    
protected:
	int posX = (WINDOW_WIDTH / 2) - TILE_SIZE;
	int posY = 0;
public:
	Figures(FiguresType figureType, sf::Color figureColor, std::vector<std::vector<int>> figureShape, int initialRotationState)
		: type(figureType), color(figureColor), shape(figureShape), rotationState(initialRotationState) {}
    Figures(const Figures& other)
        : type(other.type),
        shape(other.shape),
        color(other.color),
        rotationState(other.rotationState)
    {}

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
	void rotate(std::vector<std::vector<sf::Color>>& colorMap, sf::Keyboard::Key key);
    bool checkCollisionsAtSpawn(std::vector<std::vector<sf::Color>>& colorMap);
    void drawNext(sf::RenderWindow& window, int next);
    void drawGhost(sf::RenderWindow& window, std::vector<std::vector<sf::Color>>& colormap);
    bool isValidPosition(int posY, const std::vector<std::vector<sf::Color>>& colormap);
    int getGhostPosition();
    void isSpacePressed(bool KeyPressed);
    void swapTetrominos(std::unique_ptr<Figures>& tetromin, std::queue<int>& tetrominoQueue);
    void drawInventory(sf::RenderWindow& window);
};

const std::vector<Figures> Tetrominos = {

    Figures(FiguresType::I, sf::Color::Cyan, {
        { 1, 1, 1, 1 }
    }, 0),
    Figures(FiguresType::I, sf::Color::Cyan, {
        { 1},
        { 1},
        { 1},
        { 1}
    }, 1),
   Figures(FiguresType::I, sf::Color::Cyan, {
        { 1, 1, 1, 1 }
    }, 2),
    Figures(FiguresType::I, sf::Color::Cyan, {
        { 1},
        { 1},
        { 1},
        { 1}
    }, 3),

    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 1, 0},
        { 1, 0},
        { 1, 1},
    }, 0),
    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 0, 0, 1 },
        { 1, 1, 1 },
    }, 1),
    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 1, 1},
        { 0, 1},
        { 0, 1}
    }, 2),
    Figures(FiguresType::L, sf::Color(255, 165, 0), {
        { 1, 1, 1 },
        { 1, 0, 0 },
    }, 3),

    Figures(FiguresType::J, sf::Color::Green, {
        { 1, 1},
        { 1, 0},
        { 1, 0},
    }, 0),

    Figures(FiguresType::J, sf::Color::Green, {
        { 1, 0, 0 },
        { 1, 1, 1 },
    }, 1),
    Figures(FiguresType::J, sf::Color::Green, {
        { 0, 1},
        { 0, 1},
        { 1, 1}
    }, 2),

    Figures(FiguresType::J, sf::Color::Green, {
        { 1, 1, 1 },
        { 0, 0, 1 },
    }, 3),

    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, 0),
    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, 1),
    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, 2),
    Figures(FiguresType::O, sf::Color::Yellow, {
        { 1, 1 },
        { 1, 1 }
    }, 3),

    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 1, 0 },
        { 1, 1 },
        { 1, 0 }
    }, 0),
    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 0, 1, 0 },
        { 1, 1, 1 }
    }, 1),
    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 0, 1 },
        { 1, 1 },
        { 0, 1 }
    }, 2),
    Figures(FiguresType::T, sf::Color(128, 0, 128), {
        { 1, 1, 1 },
        { 0, 1, 0 }
    }, 3),

    Figures(FiguresType::S, sf::Color::Red, {
        { 0, 1, 1 },
        { 1, 1, 0 }
    }, 0),
    Figures(FiguresType::S, sf::Color::Red, {
        { 1, 0 },
        { 1, 1 },
        { 0, 1 }
    }, 1),
        Figures(FiguresType::S, sf::Color::Red, {
        { 0, 1, 1 },
        { 1, 1, 0 }
    }, 2),
    Figures(FiguresType::S, sf::Color::Red, {
        { 1, 0 },
        { 1, 1 },
        { 0, 1 }
    }, 3),

    Figures(FiguresType::Z, sf::Color::Blue, {
        { 1, 1, 0 },
        { 0, 1, 1 }
    }, 0),
    Figures(FiguresType::Z, sf::Color::Blue, {
        { 0, 1 },
        { 1, 1 },
        { 1, 0 }
    }, 1),
    Figures(FiguresType::Z, sf::Color::Blue, {
        { 1, 1, 0 },
        { 0, 1, 1 }
    }, 2),
    Figures(FiguresType::Z, sf::Color::Blue, {
        { 0, 1 },
        { 1, 1 },
        { 1, 0 }
    }, 3)
};


