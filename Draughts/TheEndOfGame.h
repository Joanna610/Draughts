#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Winner.h"

class TheEndOfGame
{
private:
	sf::RenderWindow* window;
	sf::RectangleShape background;
	sf::Event event;

	sf::Text text;
	sf::Text winner;
	sf::Font font;
public:
	TheEndOfGame();
	~TheEndOfGame();

	bool isOpen();
	void initTheEnd();
	void initFont();
	void initText();
	void initBackground();
	
	void whoWin(int winner);
	void draw();
	void update();
	void render();
};

