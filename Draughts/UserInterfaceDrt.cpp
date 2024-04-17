#include "UserInterfaceDrt.h"

void UserInterfaceDrt::initDraught(sf::Color color_) {
	this->draught.setRadius(RADIUS_OF_DRAUGHT);
	this->draught.setPointCount(100);
	this->draught.setFillColor(color_);
	this->color = color_;
}

void UserInterfaceDrt::initKing(sf::Color color_) {
	this->king.setRadius(RADIUS_OF_DRAUGHT);
	this->king.setPointCount(100);
	this->king.setFillColor(color_); 
}

void UserInterfaceDrt::addNewDraught(int horizontal_field, int vertical_field) {
	this->draught.setPosition(horizontal_field, vertical_field);
	this->set_of_draught.push_back(this->draught);
}

void UserInterfaceDrt::setFirstPosition() {
	this->first_position = this->set_of_draught[0].getPosition();
}

void UserInterfaceDrt::movementAI(sf::RenderWindow* window, Board& board, int Draught) {

	int max_value = 0, value = 0, x = 0, y = 0, draught = 0, final_x = 0, final_y = 0;
	Board board_copy, final_movement;
	
	for (int i = 0; i < this->set_of_draught.size(); i++) {
		this->getPositionOnBoard(this->set_of_draught[i], x, y);
		board_copy = board;
		
		value = draught_AI.max(board_copy, i, x, y, Draught);
		if (value > max_value) {
			max_value = value;
			draught = i;
			final_movement = board_copy;
			final_x = x, final_y = y;
		}
	}

	// ERRORR
	Draught = draught_AI.changeColor(Draught);

	if (max_value >= capturing_draught) { // if there was a capturing
		removeDrtsBasedOnBoard(final_movement, board, Draught);
	}

	this->setPosition_(draught, final_x, final_y);
	this->drawDraughts(window);
	board = final_movement;
}

// ERROR
void UserInterfaceDrt::removeDrtsBasedOnBoard(Board final_board, Board current_board, int draught) {
	for (int x = 0; x < AMOUNT_OF_FIELDS; x++) {
		for (int y = 0; y < AMOUNT_OF_FIELDS; y++) {
			if (current_board[x][y] == draught &&
				final_board[x][y] == BlackField) {
				sf::Vector2f wek;
				wek.x = x; wek.y = y;
				this->remove(wek);
				this->isCapturing = true;
				this->position_of_captured_draught.x = x;
				this->position_of_captured_draught.y = y;
			}
		}
	}
}

void UserInterfaceDrt::getPositionOnBoard(sf::CircleShape draught, int& x, int& y) {
	x = draught.getPosition().x / 100;
	y = draught.getPosition().y / 100;
}

void UserInterfaceDrt::setPosition_(int numberOfDraught, int x, int y) {
	sf::Vector2f newPosition;

	// converion from board coordination to coordination on platform
	newPosition.x = x* SIZE_OF_FIELD + 2 * (DISTANCE_DRAUGHT) +  RADIUS_OF_DRAUGHT ;
	newPosition.y = y * SIZE_OF_FIELD + 2 * (DISTANCE_DRAUGHT) + RADIUS_OF_DRAUGHT;

	this->set_of_draught[numberOfDraught].setPosition(newPosition);
}


void UserInterfaceDrt::movement(sf::Event event, Board& board) {

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {
			for (int i = 0; i < this->set_of_draught.size(); i++) {
				if (this->set_of_draught[i].getGlobalBounds().contains(mouse.getMousePosV())) {
					this->isMoveB = true; this->help = i;
					this->x = mouse.getMousePosW().x - this->set_of_draught[i].getPosition().x;
					this->y = mouse.getMousePosW().y - this->set_of_draught[i].getPosition().y;

					this->first_position.x = this->set_of_draught[i].getPosition().x;
					this->first_position.y = this->set_of_draught[i].getPosition().y;
				}
			}
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.key.code == sf::Mouse::Left) {
			if (this->isMoveB == true) {
				this->isMoveB = false;

				if (checkingPositionAbroad()) {
					sf::Vector2f p = this->set_of_draught[this->help].getPosition();
					sf::Vector2f newPos = sf::Vector2f(WIDTH_OUTLINE + DISTANCE_DRAUGHT + (SIZE_OF_FIELD) * int(p.x / SIZE_OF_FIELD),
						HEIGHT_OUTLINE + DISTANCE_DRAUGHT + ((SIZE_OF_FIELD) * int(p.y / SIZE_OF_FIELD)));

					sf::Vector2f newPosition, lastPosition;

					lastPosition.x = int(first_position.x / 100);
					lastPosition.y = int(first_position.y / 100);

					newPosition.x = int(newPos.x / 100);
					newPosition.y = int(newPos.y / 100);

					if (board.getPosition(newPosition.x, newPosition.y) == BlackField
						&& checkingPosition(newPos, board, newPosition, lastPosition)) {
						if (!changeIntoKing(newPos, board)) {
							this->set_of_draught[this->help].setPosition(newPos);
							int pos1[2], pos2[2];
							pos1[0] = lastPosition.x;
							pos1[1] = lastPosition.y;
							pos2[0] = newPosition.x;
							pos2[1] = newPosition.y;
							board.movementBoard(this->help, pos1[0], pos1[1], pos2[0], pos2[1]);
						}
						else {
							board.removeDraught(lastPosition.x, lastPosition.y);
						}
					}
					else {
						this->set_of_draught[this->help].setPosition(first_position);
					}
				}
				else {
					this->set_of_draught[this->help].setPosition(first_position);
				}
			}
		}
	}
}

void UserInterfaceDrt::update_() {
	if (this->isMoveB) this->set_of_draught[this->help].setPosition(mouse.getMousePosW().x - this->x,
		mouse.getMousePosW().y - this->y);
}

void UserInterfaceDrt::drawDraughts(sf::RenderWindow* window) {
	for (auto i = 0; i < this->set_of_draught.size(); i++) {
		window->draw(this->set_of_draught[i]);
	}
}

void UserInterfaceDrt::updateMouse(sf::RenderWindow* window) {
	mouse.upadeteMousePosition(window);
}

bool UserInterfaceDrt::checkingPositionAbroad() {

	sf::Vector2f position = this->set_of_draught[this->help].getPosition();

	// check if player want to put the draught abroad
	if (position.x < WIDTH_OUTLINE ||
		position.x > SIZE_OF_FIELD * AMOUNT_OF_FIELDS ||
		position.y < HEIGHT_OUTLINE ||
		position.y > SIZE_OF_FIELD * AMOUNT_OF_FIELDS) {
		return false;
	}
	else {
		return true;
	}
}

bool UserInterfaceDrt::checkingPosition(sf::Vector2f newPos, Board& board, sf::Vector2f nP, sf::Vector2f lP) {
	sf::Vector2f difference = newPos - this->first_position;

	if (board.getPosition(lP.x, lP.y) == this->getDraught()) {
		if (this->checkDirection(difference))
		{
			return true;
		}
		// check if there are any capturing
		else if (abs(difference.x) == 200 && abs(difference.y) == 200) {
			return checkCapturing(board, nP, lP, this->getDraught());
		}
	}
	else { // if draught is a black King
		if (abs(difference.x) == abs(difference.y)) {
			int return_ = checkCapturingByKing(board, nP, lP, this->getDraught());
			if (return_ == 1 || return_ == 0) return true;
			else return false;
		}
	}
	return false;
}

// function checking if draught want to make a move
bool UserInterfaceDrt::checkCapturing(Board& board, sf::Vector2f nP, sf::Vector2f lP, int draught) {

	int x = (abs(lP.x + nP.x)) / 2;
	int y = (abs(lP.y + nP.y)) / 2;

	// 1 - draught = the oposite color of draught
	// 5 - draught = the oposite color of king

	if (board.getPosition(x, y) == 1 - draught || board.getPosition(x, y) == 5 - draught) {
		if (draught == BlackDraught || draught == BlackKing) {
			board.addBPoint();
		}
		else board.addWPoint();
		
		board.removeDraught(x, y);

		this->isCapturing = true;
		this->position_of_captured_draught.x = x;
		this->position_of_captured_draught.y = y;

		return true;
	}
	else return false;
}

sf::Vector2f UserInterfaceDrt::getPositionOfCapturesDraught() {
	return this->position_of_captured_draught;
}

int UserInterfaceDrt::findDraught(sf::Vector2f wek) {
	sf::Vector2f pom;
	int i = 0;
	for (i = 0; i < set_of_draught.size(); i++) {
		pom.x = int(set_of_draught[i].getPosition().x / 100);
		pom.y = int(set_of_draught[i].getPosition().y / 100);
		if (pom.x == wek.x && pom.y == wek.y) {
			return i;
		}
	}
	return -1; // lack
}

void UserInterfaceDrt::remove(sf::Vector2f wek) {

	int number = findDraught(wek);

	std::vector <sf::CircleShape>::iterator it;
	it = this->set_of_draught.begin();
	for (int j = 0; j < number; j++) {
		it++;
	}
	this->set_of_draught.erase(it);
}

bool UserInterfaceDrt::changeIntoKing(sf::Vector2f pos, Board& board) {
	// checking if draught is in the end of the oposite side
	if (int(pos.y / 100) == this->getFnalLine()) {
		sf::Vector2f wek;
		wek.x = int(pos.x / 100);
		wek.y = int(pos.y / 100);
		int number = this->findDraught(wek);

		this->king.setPosition(pos);
		this->set_of_draught[number] = this->king;
		board.setPosition(number, wek.x, wek.y, this->getKing());

		return true;
	}
	else return false;
}

int UserInterfaceDrt::checkCapturingByKing(Board& board, sf::Vector2f nP, sf::Vector2f lP, int draught) {
	int distance_x = nP.x - lP.x, distance_y = nP.y - lP.y;
	sf::Vector2f p;
	int amount_od_drught = 0, pos = 0;
	for (int i = 1; i < abs(distance_x); i++) {
		if (distance_x < 0 && distance_y < 0) {
			pos = board.getPosition(lP.x - i, lP.y - i);
			if (pos == 1 - draught || pos == 5 - draught) {
				amount_od_drught++;
				p.x = lP.x - i;
				p.y = lP.y - i;
			}
			if (pos == draught || pos == 4+ draught) return -1; // error
		}
		else if (distance_x < 0 && distance_y > 0) {
			pos = board.getPosition(lP.x - i, lP.y + i);
			if (pos == 1 - draught || pos == 5 - draught) {
				amount_od_drught++;
				p.x = lP.x - i;
				p.y = lP.y + i;
			}
			if (pos == draught || pos == 4 + draught) return -1; // error
		}
		else if (distance_x > 0 && distance_y < 0) {
			pos = board.getPosition(lP.x + i, lP.y - i);
			if (pos == 1 - draught || pos == 5 - draught) {
				amount_od_drught++;
				p.x = lP.x + i;
				p.y = lP.y - i;
			}
			if (pos == draught || pos == 4 + draught) return -1; // error
		}
		else if (distance_x > 0 && distance_y > 0) {
			pos = board.getPosition(lP.x + i, lP.y + i);
			if (pos == 1 - draught || pos == 5 - draught) {
				amount_od_drught++;
				p.x = lP.x + i;
				p.y = lP.y + i;
			}
			if (pos == draught || pos == 4 + draught) return -1; // error
		}
	}

	if (amount_od_drught > 1) return -1; // incorrect capturing
	else if (amount_od_drught == 1) {
		capturingByKing(board, p);
		return 1; // there is a draught to capture
	}
	else return 0; // there is no capturing	
}

void UserInterfaceDrt::capturingByKing(Board& board, sf::Vector2f pos) {
	
	if (this->getDraught() == BlackDraught || this->getKing() == BlackKing) board.addBPoint();
	else board.addWPoint();
	board.removeDraught(pos.x, pos.y);
	this->isCapturing = true;
	this->position_of_captured_draught.x = pos.x;
	this->position_of_captured_draught.y = pos.y;
}