
#pragma once

#include "tile.h"

#define BLUE_PLAYER 0
#define WHITE_PLAYER 1
#define NO_TOKEN 2

class Board
{
private:
	Tile mBoard[8][8];
	bool mOccupied[8][8];
	int mColor[8][8];

public:
	Board();
	Tile getTile(int i, int j);
	bool getOccupied(int i, int j);
	void setOccupied(int i, int j);
	void setNotOccupied(int i, int j);
	int getColor(int i, int j);
	void setColor(int i, int j, int color);
};



