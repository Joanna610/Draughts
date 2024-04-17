#pragma once

#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "UserInterfaceDrt.h" 

class UsrInterfaceBlackDrts: public UserInterfaceDrt {

public:
	UsrInterfaceBlackDrts() {}
	~UsrInterfaceBlackDrts() {}

	void initBlackDraughts(sf::Color color);
	bool checkDirection(sf::Vector2f distance) override;
	int getDraught() override;
	int getKing() override;
	int getFnalLine() override;
};

