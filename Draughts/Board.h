#pragma once

#include "BoardDimensions.h"
#include "BoardElem.h"
#include "Points.h"
#include "Elements.h"

#include <iostream>
#include <vector>

class Board
{
private:
	int board[AMOUNT_OF_FIELDS][AMOUNT_OF_FIELDS];
	std::vector<Elements> white_drts;
	std::vector<Elements> black_drts;
	int points_white = 0, points_black = 0;
	Elements board_white_drts[AMOUNT_OF_DRAUGHTS];
	Elements board_black_drs[AMOUNT_OF_DRAUGHTS];

	int amount_of_white_draughts = AMOUNT_OF_DRAUGHTS;
	int amount_of_black_draughts = AMOUNT_OF_DRAUGHTS;
public:
	
	Board();
	~Board();

	void copyBoard(Board board_);

	int* operator[](int index) { return board[index]; }
	Board(Board& board_); 
	 Board& operator =( Board& board_copy);
	 

	void initBoard();
	void movementBoard(int drt, int x1, int y1, int x2, int y2);
	void moveWhiteDraught(int drt, int x2, int y2);
	void moveBlackDraught(int drt, int x2, int y2);

	void showBoard();
	int getPosition(int x, int y);
	void setPosition(int drt, int x, int y, int draught);

	void removeDraught(int x, int y);

	void addWPoint();
	void addBPoint();
	int getWPoints();
	int getBPoints();
	int getBlackDraught();
	int getWhiteDraugth();

	int checkVictory();
	bool checkPositionAbroad(int x2, int y2);
	bool checkBlackField(int x, int y);
	int checkDirection(int x1, int y1, int x2, int y2, int draught);
	int checkCapturing(int x1, int y1, int distance_x, int distance_y, int draught);
};


