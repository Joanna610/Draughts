#include "Button.h"

Button::Button() {
}

Button::~Button() {
}

void Button::setFont_() {

	if (!this->font.loadFromFile("./arial.ttf")) {
		// error...
		std::cout << "sth goes wrong \n";
	}
	this->text.setFont(this->font);
}



void Button::initButton(std::string text_, int charSize, sf::Vector2f size, sf::Color color, sf::Color color_of_text) {
	this->text.setString(text_);
	this->text.setFillColor(color_of_text);
	this->text.setCharacterSize(charSize);

	this->button.setSize(size);
	this->button.setFillColor(color);

	this->setFont_();
}


void Button::setBackColor(sf::Color color) {
	this->button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	this->text.setFillColor(color);
}

void Button::setPos(sf::Vector2f position) {
	this->button.setPosition(position);

	float x = (position.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
	float y = (position.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);

	this->text.setPosition({ x, y });
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(this->button);
	window.draw(this->text);
}

bool Button::is_mouse_on_button(sf::RenderWindow& window) {
	float MousePosX = sf::Mouse::getPosition(window).x;
	float MousePosY = sf::Mouse::getPosition(window).y;

	float ButtonPosX_beginning = this->button.getPosition().x;
	float ButtonPosY_beginning = this->button.getPosition().y;

	float ButtonPosX_ending = ButtonPosX_beginning + this->button.getLocalBounds().width;
	float ButtonPosY_ending = ButtonPosY_beginning + this->button.getLocalBounds().height;

	if (MousePosX < ButtonPosX_ending && MousePosY < ButtonPosY_ending && MousePosX > ButtonPosX_beginning && MousePosY > ButtonPosY_beginning) {
		return true;
	}
	return false;
}
