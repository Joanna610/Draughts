#pragma once

#include "Board.h"
#include "BoardElem.h"

#define ALLMOVEMENTS 8


class ArtificialIntelligence
{
	int tabMovementDraught[ALLMOVEMENTS][2]; // draught can make eight movemnt indeon color
	int iteration = 3;
public:
	ArtificialIntelligence();
	~ArtificialIntelligence(){}

	int movement(int drt, Board& board, int x1, int y1, int x2, int y2, int Draught);
	int max(Board& board, int drt, int& x, int& y, int Draught);
	int min(Board& board, int& x, int& y, int Draught);
	int changeColor(int Draught);
};

