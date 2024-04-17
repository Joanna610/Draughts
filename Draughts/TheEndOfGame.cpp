#include "TheEndOfGame.h"
#include "Button.h"

TheEndOfGame::TheEndOfGame() {
	this->window = new sf::RenderWindow({ 700, 500 }, "End", sf::Style::Titlebar | sf::Style::Close);
	this->initTheEnd();
}

TheEndOfGame::~TheEndOfGame() {
	delete this->window;
}

void TheEndOfGame::initTheEnd() {
	this->initBackground();
	this->initText();
}

bool TheEndOfGame::isOpen() {
	return this->window->isOpen();
}

void TheEndOfGame::initFont() {
	if (!this->font.loadFromFile("arial.ttf")) {
		// error...
		std::cout << "Woopsy doopsy, sth goes wrong \n";
	}
}

void TheEndOfGame::whoWin(int winner) {

	switch (winner)
	{ 
		case WhiteDraughts_win:
			this->winner.setString("White draughts win !!!");
		break;
		case BlackDraughts_win:
			this->winner.setString("Black draughts win !!!");
		break;
		default:
			this->winner.setString("Remis !!!");
			this->winner.setPosition(230.f, 250.f);
		break;
	}
	
}

void TheEndOfGame::initText() {
	this->initFont();
	this->winner.setFont(this->font);
	this->winner.setCharacterSize(50);
	this->winner.setFillColor(sf::Color::White);
	this->winner.setPosition(120.f, 250.f);

	this->text.setFont(this->font);
	this->text.setString("The End");
	this->text.setCharacterSize(70);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(200.f, 110.f);
}

void TheEndOfGame::initBackground() {
	// the background of game
	this->background.setSize(sf::Vector2f(700, 500));
	this->background.setFillColor(sf::Color(17, 63, 61));
	this->background.setPosition(0.f, 0.f);
}

void TheEndOfGame::draw() {
	this->window->draw(this->background);
	this->window->draw(this->text);
	this->window->draw(this->winner);
}

void TheEndOfGame::update() {
	while (window->pollEvent(this->event)) {
		if (event.type == sf::Event::Closed)
			this->window->close();
	}
}

void TheEndOfGame::render() {
	this->window->clear();
	this->draw();
	this->window->display();
}

