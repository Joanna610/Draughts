#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class Button
{
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Font font;

public:
	Button();
	~Button();

	void setFont_();
	void initButton(std::string text_, int charSize, sf::Vector2f size, sf::Color color, sf::Color color_of_text);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPos(sf::Vector2f position);
	

	void draw(sf::RenderWindow& window);
	bool is_mouse_on_button(sf::RenderWindow& window);
};

