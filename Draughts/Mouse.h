#pragma once

#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

class Mouse
{
private:
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
public:
	void upadeteMousePosition(sf::RenderWindow* window);
	
	sf::Vector2i getMousePosW();
	sf::Vector2f getMousePosV();
};

