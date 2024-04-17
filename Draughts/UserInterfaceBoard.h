#pragma once

#include <vector>
#include <sstream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "UserInterfaceWhtDrts.h"
#include "UsrInterfaceBlackDrts.h"
#include "Board.h"
#include "TheEndOfGame.h"

class UserInterfaceBoard
{
private:
	sf::RenderWindow* window;
	sf::Event event;

	sf::RectangleShape background;
	sf::RectangleShape district;
	sf::RectangleShape white_field;
	sf::RectangleShape black_field;
	sf::RectangleShape board_of_fields[AMOUNT_OF_FIELDS][AMOUNT_OF_FIELDS];

	UsrInterfaceBlackDrts blackdraught;
	UserInterfaceWhtDrts whitedraught;

	Board board;

	sf::Texture texture;
	
	sf::Font font;

	sf::Text letters[AMOUNT_OF_FIELDS*2];
	char board_of_letters[AMOUNT_OF_FIELDS] = { 'A', 'B', 'C', 'D','E', 'F', 'G', 'H' };

	sf::Text numbers[AMOUNT_OF_FIELDS * 2];
	char board_of_numbers[AMOUNT_OF_FIELDS] = { '1', '2', '3', '4', '5', '6', '7', '8' };

	sf::Text amount_of_points[4];
	bool theEnd = false;

public:
	UserInterfaceBoard();
	~UserInterfaceBoard();

	bool isOpen();

	void initBoardElements();
	void initBackground();
	void initDistrict();
	void initFont();
	void initLetters();
	void initNumbers();
	void initText();
	void updateText();
	void initWhiteField();
	void initBlackField();
	void initBoard();

	void removeWhiteDraught();
	void removeBlackDraught();

	// draw
	void drawBoard();
	void drawDraughts();
	void _draw();

	// update
	void upadeteMousePosition(); 
	void updateDraughts(int Draught);
	
	// render
	void update(int Draught);
	void render();

};

