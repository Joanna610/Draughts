#pragma once

#include <vector>
#include <cmath>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "Mouse.h"
#include "BoardDimensions.h" 
#include "Board.h" 
#include "ArtificialIntelligence.h"

class UserInterfaceDrt
{	
	sf::CircleShape draught;
	sf::CircleShape king;
	std::vector<sf::CircleShape> set_of_draught;
	sf::Vector2f first_position;
	sf::Vector2f position_of_captured_draught;
	sf::Color color;
	ArtificialIntelligence draught_AI;

	int isMoveW = 0, isMoveB = 0, x = 0, y = 0, help = 0;
	bool isCapturing = false;
	bool UserTurn = true; // !!!!!
	int direction[2]; // in which ways the draught can move

	Mouse mouse;

public:

	inline bool getWhichTurn() { return UserTurn; }
	inline bool getIsCapturng() { return isCapturing; }
	inline void setUserTurn(bool value) { UserTurn = value; }
	inline void setIsCapturing() { isCapturing = false; }
	

	void initDraught(sf::Color color_);
	void initKing(sf::Color color_);
	void addNewDraught(int horizontal_field, int vertical_field);
	void setFirstPosition();
	sf::Vector2f getFirstPosition() { return this->first_position; }

	void setPosition_(int numberOfDraught, int x, int y);
	void movementAI(sf::RenderWindow* window, Board& board, int Draught);
	void movement(sf::Event event, Board& board);
	void drawDraughts(sf::RenderWindow* window);
	void update_();
	void updateMouse(sf::RenderWindow* window);

	bool checkingPositionAbroad();
	bool checkingPosition(sf::Vector2f newPos, Board& board, sf::Vector2f nP, sf::Vector2f lP); // ***** ***
	virtual bool checkDirection(sf::Vector2f distance) = 0;
	virtual int getDraught() = 0;
	virtual int getFnalLine() = 0;
	virtual int getKing() = 0;
	void removeDrtsBasedOnBoard(Board final_board, Board current_board, int draught);

	bool checkCapturing(Board& board, sf::Vector2f nP, sf::Vector2f lP, int draught); // ***** ***
	
	sf::Vector2f getPositionOfCapturesDraught();
	int findDraught(sf::Vector2f wek);
	void remove(sf::Vector2f wek);
	bool changeIntoKing(sf::Vector2f pos, Board& board); // ***** ***
	int checkCapturingByKing(Board& board, sf::Vector2f nP, sf::Vector2f lP, int draught); // ***** ***
	void capturingByKing(Board& board, sf::Vector2f pos);
	void drawDraughtsBoard(sf::RenderWindow* window);
	void getPositionOnBoard(sf::CircleShape draught, int& x, int& y);
};

