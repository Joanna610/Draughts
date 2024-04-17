#include "Menu.h"

Menu::Menu() {	
	this->window = new sf::RenderWindow({470, 700 }, "Menu", sf::Style::Titlebar | sf::Style::Close);
	this->initMenu();
}

Menu::~Menu() {
	delete this->window;
}

void Menu::initMenu() {
	this->initMenuTexture();
	this->initText();
	this->initButton();
}

void Menu::initMenuTexture() {
	if (!this->texture.loadFromFile("chessboard.png"))
	{
		std::cout << " sth goes wrong, ... again \n";
		// error...
	}
	this->texture.setSmooth(true);
	// position
	//this->sprite.setPosition(sf::Vector2f(10.f, 50.f)); // absolute position
	this->sprite.move(sf::Vector2f(470.f, 0.f)); // offset relative to the current position

	// rotation
	this->sprite.setRotation(90.f); // absolute angle
	//this->sprite.rotate(90.f); // offset relative to the current angle

	// scale
	//this->sprite.setScale(sf::Vector2f(0.5f, 2.f)); // absolute scale factor
	this->sprite.scale(sf::Vector2f(0.4f, 0.4f)); // factor relative to the current scale
	
	this->sprite.setTexture(this->texture);
}

void Menu::initFont() {
	if (!this->font.loadFromFile("./arial.ttf")) {
		// error...
		std::cout << "sth goes wrong \n";
	}
	this->text.setFont(this->font);
}

void Menu::initText() {
	this->initFont();
	this->text.setFont(this->font);
	this->text.setString("MENU");
	this->text.setCharacterSize(120);
	this->text.setFillColor(sf::Color(0,0,0));
	this->text.setPosition(70.f, 50.f);
}

void Menu::initButton() {
	this->white_draughts.initButton("White draughts", 30, { 300, 70 }, sf::Color(122,71, 71), sf::Color::White);
	this->white_draughts.setPos({100, 300});

	this->black_draughts.initButton("Black draughts", 30, { 300, 70 }, sf::Color(122, 71, 71), sf::Color::White);
	this->black_draughts.setPos({ 100, 420 });

	this->exit.initButton("Exit", 30, { 300, 70 }, sf::Color(122, 71, 71), sf::Color::White);
	this->exit.setPos({ 100, 540 });

}

bool Menu::isOpen() {
	return this->window->isOpen();
}

int Menu::update() {
	while (window->pollEvent(this->event)) {
		if (event.type == sf::Event::Closed) 
			this->window->close();

		return this->_update(window);
	}
}

int Menu::_update(sf::RenderWindow* window) {
	if (this->event.type == sf::Event::MouseMoved) {
		if (this->white_draughts.is_mouse_on_button(*window)) {
			this->white_draughts.setBackColor(sf::Color(189, 154, 154));
		}
		else this->white_draughts.setBackColor(sf::Color(122, 71, 71));

		if (this->black_draughts.is_mouse_on_button(*window)) {
			this->black_draughts.setBackColor(sf::Color(189, 154, 154));
		}
		else this->black_draughts.setBackColor(sf::Color(122, 71, 71));

		if (this->exit.is_mouse_on_button(*window)) {
			this->exit.setBackColor(sf::Color(189, 154, 154));
		}
		else this->exit.setBackColor(sf::Color(122, 71, 71));
	}
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {
			if (this->white_draughts.is_mouse_on_button(*window)) {
				window->close();
				return 0;
			}
			else if (this->black_draughts.is_mouse_on_button(*window)) {
				window->close();
				return 1;
			}
			else if (this->exit.is_mouse_on_button(*window)) {
				window->close();
			}
		}
	}
	return -1;
}

void Menu::drawMenu(sf::RenderWindow* window) {
	window->draw(this->sprite);
	window->draw(this->text);
} 

void Menu::drawButtons(sf::RenderWindow* window) {
	this->white_draughts.draw(*window);
	this->black_draughts.draw(*window);
	this->exit.draw(*window);
}

void Menu::render() {
	this->window->clear();
	this->drawMenu(this->window);
	this->drawButtons(this->window);
	this->window->display();
}