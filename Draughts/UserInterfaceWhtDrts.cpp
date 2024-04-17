#include "UserInterfaceWhtDrts.h"

void UserInterfaceWhtDrts::initWhiteDraughts(sf::Color color) {

	initDraught(color);
	int horizontal_field = 0, vertical_field = HEIGHT_OUTLINE + 5 * SIZE_OF_FIELD + DISTANCE_DRAUGHT;

	for (int i = 0; i < 3; i++) {

		if (i % 2 == 0) {
			horizontal_field = WIDTH_OUTLINE + DISTANCE_DRAUGHT;

			for (int j = 0; j < 4; j++) {
				addNewDraught(horizontal_field, vertical_field);
				horizontal_field += 2 * SIZE_OF_FIELD;
			}
			vertical_field += SIZE_OF_FIELD;
		}
		else {
			horizontal_field = WIDTH_OUTLINE + SIZE_OF_FIELD + DISTANCE_DRAUGHT;
			for (int j = 0; j < 4; j++) {

				addNewDraught(horizontal_field, vertical_field);
				horizontal_field += 2 * SIZE_OF_FIELD;
			}
			vertical_field += SIZE_OF_FIELD;
		}
	}

	// we have to initialize the first position (for example of the first draught)
	setFirstPosition();
	this->initKing(sf::Color(174, 187, 235));
}

bool UserInterfaceWhtDrts::checkDirection(sf::Vector2f distance) {
	return (distance.x == 100 && distance.y == -100) ||
		(distance.x == -100 && distance.y == -100);
}

int UserInterfaceWhtDrts::getDraught() {
	return WhiteDraught;
}

int UserInterfaceWhtDrts::getKing() {
	return WhiteKing;
}

int UserInterfaceWhtDrts::getFnalLine() {
	return 0;
}

