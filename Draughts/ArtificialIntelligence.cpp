#include "ArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence(){

	this->tabMovementDraught[0][0] = 1;
	this->tabMovementDraught[0][1] = 1;
	this->tabMovementDraught[1][0] = 1;
	this->tabMovementDraught[1][1] = -1;
	this->tabMovementDraught[2][0] = -1;
	this->tabMovementDraught[2][1] = 1;
	this->tabMovementDraught[3][0] = -1;
	this->tabMovementDraught[3][1] = -1;

	this->tabMovementDraught[4][0] = 2;
	this->tabMovementDraught[4][1] = 2;
	this->tabMovementDraught[5][0] = 2;
	this->tabMovementDraught[5][1] = -2;
	this->tabMovementDraught[6][0] = -2;
	this->tabMovementDraught[6][1] = 2;
	this->tabMovementDraught[7][0] = -2;
	this->tabMovementDraught[7][1] = -2;
}

int ArtificialIntelligence::changeColor(int Draught) {
	if (Draught == WhiteDraught) return BlackDraught;
	else if (Draught == BlackDraught) return WhiteDraught;
}

int ArtificialIntelligence::movement(int drt, Board& board, int x1, int y1, int x2, int y2, int Draught) {
	if (!board.checkBlackField(x2, y2)) return 0;
	if (!board.checkPositionAbroad(x2, y2)) return 0;
	
	int points = board.checkDirection(x1, y1, x2, y2, Draught);
	if(points == 0) return 0;

	board.movementBoard(drt, x1, y1, x2, y2);
	return points;
}

int ArtificialIntelligence::max(Board& board, int drt, int& x, int& y, int Draught) {
	// search movement and count points
	int enemy = changeColor(Draught);
	int points = 0, max = 0, first_pos_x = x, first_pos_y = y;
	Board copy_board, final_board;
	
	for (int i = 0; i < ALLMOVEMENTS; i++) {
		copy_board = board;

		points = this->movement(drt, copy_board, first_pos_x, first_pos_y, 
			first_pos_x + this->tabMovementDraught[i][0], 
			first_pos_y + this->tabMovementDraught[i][1], Draught);
		
		if (points != 0) { // return 0 if there is no movement
			copy_board.showBoard();
			
			if (points > max) {
				max = points;
				final_board = copy_board;
				x = first_pos_x + this->tabMovementDraught[i][0];
				y = first_pos_y + this->tabMovementDraught[i][1];		
			}
		}
	}
	board = final_board;
	return max;
}

int ArtificialIntelligence::min(Board& board, int& x, int& y, int Draught) {
	return 0;
}