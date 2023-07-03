#pragma once
#include "Figures.h"

class Game: private Figures {
private:
	int score;
	float speed;
public:
	Game();
	void clearRow();
	void setScore(int score);
	int getScore();
	~Game();
};