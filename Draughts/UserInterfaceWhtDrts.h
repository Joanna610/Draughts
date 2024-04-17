#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "UserInterfaceDrt.h" 

class UserInterfaceWhtDrts: public UserInterfaceDrt {

public:
	UserInterfaceWhtDrts() {}
	~UserInterfaceWhtDrts() {}

	void initWhiteDraughts(sf::Color color);
	bool checkDirection(sf::Vector2f distance) override;
	int getDraught() override;
	int getKing() override;
	int getFnalLine() override;

};

