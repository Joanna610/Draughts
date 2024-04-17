#include "Mouse.h"

void Mouse::upadeteMousePosition(sf::RenderWindow* window) {
	this->mousePosWindow = sf::Mouse::getPosition(*window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

sf::Vector2i Mouse::getMousePosW() {
	return mousePosWindow;
}

sf::Vector2f Mouse::getMousePosV() {
	return mousePosView;
}