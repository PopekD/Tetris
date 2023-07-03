#pragma once
#include "Tile.h"

class Game {
private:
	int score;
	float time;
public:
	Game();
	void clearRow();
	void setScore(int score);
	int getScore();
	~Game();
};