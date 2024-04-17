#include<iostream>

#include "Menu.h"
#include "UserInterfaceBoard.h"


int main() {
	
	Menu menu;

	int choice = 0;
	while (menu.isOpen()) {
		choice = menu.update();
		menu.render();
	}

	if (choice == -1) return 0; // end of game
	else {
		UserInterfaceBoard board;
		
		while (board.isOpen()) {
			board.update(choice);
			board.render();
		}
	}
	return 0;
}