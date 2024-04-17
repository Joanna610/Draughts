#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

#include "Button.h"

class Menu
{
private:
	sf::RenderWindow* window;
	sf::Event event;

	// elements of menu
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text text;
	sf::Font font;

	// buttons
	Button white_draughts;
	Button black_draughts;
	Button exit;

public:
	Menu();
	~Menu();

	void initMenu();
	void initMenuTexture();
	void initFont();
	void initText();
	void initButton();
	bool isOpen();
	void mouse_click();
	int update();
	int _update(sf::RenderWindow* window);
	void drawMenu(sf::RenderWindow* window);
	void drawButtons(sf::RenderWindow* window);
	void render();

};

