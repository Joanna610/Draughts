#include "UserInterfaceBoard.h"

// konstructor 
UserInterfaceBoard::UserInterfaceBoard() {
	this->window = new sf::RenderWindow({ WIDTH_OF_GAME, HEIGHT_OF_GAME }, "Draughts", sf::Style::Titlebar | sf::Style::Close);
	this->initBoardElements();
}

// destructor
UserInterfaceBoard::~UserInterfaceBoard() {
	delete window;
}

bool UserInterfaceBoard::isOpen() {
	return  window->isOpen() && !this->theEnd;
}

void UserInterfaceBoard::initBoardElements() {
	this->initBoard();
	this->initBackground();
	this->initDistrict();
	this->initLetters();
	this->initNumbers();
	this->initText();

	blackdraught.initBlackDraughts(sf::Color(16, 12, 6));
	whitedraught.initWhiteDraughts(sf::Color(233, 223, 227));
}

// functions - initialization parametrs
void UserInterfaceBoard::initBackground() {
	// the background of game
	this->background.setSize(sf::Vector2f(WIDTH_OF_GAME, HEIGHT_OF_GAME));
	this->background.setFillColor(sf::Color(71, 57, 67));
	this->background.setPosition(0, 0);
}

void UserInterfaceBoard::initDistrict() {
	// the district with letters for board
	this->district.setSize(sf::Vector2f(AMOUNT_OF_FIELDS * SIZE_OF_FIELD + THICKNESS_OF_DISTRICT * 2,
		AMOUNT_OF_FIELDS * SIZE_OF_FIELD + THICKNESS_OF_DISTRICT * 2));
	this->district.setFillColor(sf::Color(0, 0, 0));
	this->district.setPosition(DISTRICT_WITH_NUMBERS_W, DISTRICT_WITH_NUMBERS_H);
}

void UserInterfaceBoard::initFont() {
	if (!this->font.loadFromFile("./arial.ttf")) {
		// error...
		std::cout << "sth goes wrong \n";
	}
}

void UserInterfaceBoard::initLetters() {

	// top 
	int place_of_first_letter_w = PLACE_OF_FIRST_LETTER_W;
	for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
		this->initFont();
		this->letters[i].setFont(this->font);
		this->letters[i].setString(this->board_of_letters[i]);
		this->letters[i].setCharacterSize(SIZE_OF_FONT);
		this->letters[i].setFillColor(sf::Color(255, 255, 255));
		this->letters[i].setPosition(place_of_first_letter_w, PLACE_OF_FIRST_LETTER_H);
		place_of_first_letter_w += SIZE_OF_FIELD;
	}

	// botton
	place_of_first_letter_w = PLACE_OF_FIRST_LETTER_W;
	int place_of_first_letter_h = PLACE_OF_FIRST_LETTER_H + AMOUNT_OF_FIELDS * SIZE_OF_FIELD + THICKNESS_OF_DISTRICT;
	for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
		this->letters[AMOUNT_OF_FIELDS + i].setFont(this->font);
		this->letters[AMOUNT_OF_FIELDS + i].setString(this->board_of_letters[i]);
		this->letters[AMOUNT_OF_FIELDS + i].setCharacterSize(SIZE_OF_FONT);
		this->letters[AMOUNT_OF_FIELDS + i].setFillColor(sf::Color(255, 255, 255));
		this->letters[AMOUNT_OF_FIELDS + i].setPosition(place_of_first_letter_w, place_of_first_letter_h);
		place_of_first_letter_w += SIZE_OF_FIELD;
	}
}

void UserInterfaceBoard::initNumbers() {

	// left 
	int place_of_first_number_w = PLACE_OF_FIRST_NUMBER_W;
	int place_of_first_number_h = PLACE_OF_FIRST_NUMBER_H;
	for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
		this->initFont();
		this->numbers[i].setFont(this->font);
		this->numbers[i].setString(this->board_of_numbers[i]);
		this->numbers[i].setCharacterSize(SIZE_OF_FONT);
		this->numbers[i].setFillColor(sf::Color(255, 255, 255));
		this->numbers[i].setPosition(place_of_first_number_w, place_of_first_number_h);
		place_of_first_number_h += SIZE_OF_FIELD;
	}

	// right
	place_of_first_number_w = PLACE_OF_FIRST_NUMBER_W + SIZE_OF_FIELD * AMOUNT_OF_FIELDS + THICKNESS_OF_DISTRICT;
	place_of_first_number_h = PLACE_OF_FIRST_NUMBER_H;
	for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
		this->numbers[AMOUNT_OF_FIELDS + i].setFont(this->font);
		this->numbers[AMOUNT_OF_FIELDS + i].setString(this->board_of_numbers[i]);
		this->numbers[AMOUNT_OF_FIELDS + i].setCharacterSize(SIZE_OF_FONT);
		this->numbers[AMOUNT_OF_FIELDS + i].setFillColor(sf::Color(255, 255, 255));
		this->numbers[AMOUNT_OF_FIELDS + i].setPosition(place_of_first_number_w, place_of_first_number_h);
		place_of_first_number_h += SIZE_OF_FIELD;
	}
}

void UserInterfaceBoard::initText() {
	this->initFont();
	for (int i = 0; i < 4; i++) {
		this->amount_of_points[i].setCharacterSize(25);
		this->amount_of_points[i].setFont(this->font);
		this->amount_of_points[i].setFillColor(sf::Color(255, 255, 255));
	}

	this->amount_of_points[0].setString("Points of white draughts: ");
	this->amount_of_points[0].setPosition(WIDTH_OF_GAME / 2 + 250, HEIGHT_OF_GAME / 2 + 100);

	this->amount_of_points[1].setString('0');
	this->amount_of_points[1].setPosition(WIDTH_OF_GAME / 2 + 550, HEIGHT_OF_GAME / 2 + 100);

	this->amount_of_points[2].setString("Points of black draughts: ");
	this->amount_of_points[2].setPosition(WIDTH_OF_GAME / 2 + 250, HEIGHT_OF_GAME / 2 + 200);

	this->amount_of_points[3].setString('0');
	this->amount_of_points[3].setPosition(WIDTH_OF_GAME / 2 + 550, HEIGHT_OF_GAME / 2 + 200);
}

void UserInterfaceBoard::updateText() {
	std::ostringstream os, os2;
	os << board.getWPoints();
	this->amount_of_points[1].setString(os.str());
	os2 << board.getBPoints();
	this->amount_of_points[3].setString(os2.str());
}

void UserInterfaceBoard::initWhiteField() {
	this->white_field.setSize(sf::Vector2f(SIZE_OF_FIELD, SIZE_OF_FIELD));
	this->white_field.setFillColor(sf::Color(222, 212, 186));
	this->white_field.setOutlineColor(sf::Color::Black);
}

void UserInterfaceBoard::initBlackField() {
	this->black_field.setSize(sf::Vector2f(SIZE_OF_FIELD, SIZE_OF_FIELD));
	this->black_field.setFillColor(sf::Color(48, 45, 38));
	this->black_field.setOutlineColor(sf::Color::Black);
}

void UserInterfaceBoard::initBoard() {
	this->initWhiteField();
	this->initBlackField();

	int horizontal_lenght = 0, vertical_length = HEIGHT_OUTLINE;

	for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
		if (i % 2 == 0) {
			horizontal_lenght = WIDTH_OUTLINE;
			for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {
				if (j % 2 == 0) {
					this->white_field.setPosition(horizontal_lenght, vertical_length);
					board_of_fields[i][j] = this->white_field;
					horizontal_lenght += SIZE_OF_FIELD;
				}
				else {
					this->black_field.setPosition(horizontal_lenght, vertical_length);
					board_of_fields[i][j] = this->black_field;
					horizontal_lenght += SIZE_OF_FIELD;
				}
			}
			vertical_length += SIZE_OF_FIELD;
		}
		else {
			horizontal_lenght = WIDTH_OUTLINE;
			for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {

				if (j % 2 == 0) {
					this->black_field.setPosition(horizontal_lenght, vertical_length);
					board_of_fields[i][j] = this->black_field;
					horizontal_lenght += SIZE_OF_FIELD;
				}
				else {
					this->white_field.setPosition(horizontal_lenght, vertical_length);
					board_of_fields[i][j] = this->white_field;
					horizontal_lenght += SIZE_OF_FIELD;
				}
			}
			vertical_length += SIZE_OF_FIELD;
		}
	}
}

// removing draught
void UserInterfaceBoard::removeWhiteDraught() {
	whitedraught.remove(blackdraught.getPositionOfCapturesDraught());
	blackdraught.setIsCapturing();
}

void UserInterfaceBoard::removeBlackDraught() {
	blackdraught.remove(whitedraught.getPositionOfCapturesDraught());
	whitedraught.setIsCapturing();
}

// *****************************************
//					draw
// ***************************************** 

void UserInterfaceBoard::drawBoard() {

	this->window->draw(this->background);
	this->window->draw(this->district);

	for (int i = 0; i < AMOUNT_OF_FIELDS * 2; i++) {
		this->window->draw(this->letters[i]);
	}

	for (int i = 0; i < AMOUNT_OF_FIELDS * 2; i++) {
		this->window->draw(this->numbers[i]);
	}

	for (int i = 0; i < 4; i++)
		this->window->draw(this->amount_of_points[i]);

	for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
		for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {
			this->window->draw(board_of_fields[i][j]);
		}
	}
}

void UserInterfaceBoard::drawDraughts() {
	blackdraught.drawDraughts(this->window);
	whitedraught.drawDraughts(this->window);
}

void UserInterfaceBoard::_draw() {
	this->drawBoard();
	this->drawDraughts();
}

// ============================== MOVEMENT ==============================

void UserInterfaceBoard::upadeteMousePosition() { // nazwe poprawic
	blackdraught.updateMouse(this->window);
	whitedraught.updateMouse(this->window);
}

void UserInterfaceBoard::updateDraughts(int Draught) {
	//if (Draught == BlackDraught) {
		//if (blackdraught.getWhichTurn()) {
			blackdraught.movement(this->event, this->board);
			blackdraught.update_();
			if (blackdraught.getIsCapturng()) {
				this->removeWhiteDraught();
				if (this->board.checkVictory() == 1) {
					std::cout << "victory of black draughts" << std::endl;
					this->theEnd = true;
				}
			}
		/* }
		else {
			whitedraught.movementAI(this->window, this->board, WhiteDraught);
			blackdraught.setUserTurn(true);
		}
	}
	else {*/
		if (whitedraught.getWhichTurn()) {
			whitedraught.movement(this->event, this->board);
			whitedraught.update_();
			if (whitedraught.getIsCapturng()) {
				this->removeBlackDraught();
				if (this->board.checkVictory() == 0) {
					std::cout << "victory of white draughts" << std::endl;
					this->theEnd = true;
				}
			}
		}/*
		else {
			blackdraught.movementAI(this->window, this->board, BlackDraught);
			whitedraught.setUserTurn(true);
		}
	}*/
}

// function updating and rendering

void UserInterfaceBoard::update(int Draught) {
	this->upadeteMousePosition();
	while (window->pollEvent(this->event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();

		this->updateDraughts(Draught);
		this->updateText(); // indicate the number of points
	}

	if (this->theEnd) { // open window when someone wins
		TheEndOfGame end;
		end.whoWin(board.checkVictory());
		while (end.isOpen()) {
			end.update();
			end.render();
		}
	}
}

void UserInterfaceBoard::render() {
	window->clear();
	this->_draw();
	window->display();
}
