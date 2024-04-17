#include "Board.h"

Board::Board() {
    this->initBoard();
}

Board::~Board() {
}

Board::Board(Board& board_) {
    for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
        for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {
            (*this)[i][j] = board_[i][j];
        }
    }
}

void Board::copyBoard(Board board_) {
    for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
        for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {
            (*this)[i][j] = board_[i][j];
        }
    }
}

Board& Board::operator = ( Board& board_) {

    for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
        for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {
            (*this)[i][j] = board_[i][j];   
        }
    }

    for (int i = 0; i < board_.white_drts.size(); i++) {
        if (i >= this->white_drts.size()) {  // jesli tablica pierwotna jest za mala
            Elements elem;

            elem.setElem(board_.white_drts[i].getElem());
            elem.setX(board_.white_drts[i].getX());
            elem.setY(board_.white_drts[i].getY());

            this->white_drts.push_back(elem);
        }
        else {
            this->white_drts[i].setElem(board_.white_drts[i].getElem());
            this->white_drts[i].setX(board_.white_drts[i].getX());
            this->white_drts[i].setY(board_.white_drts[i].getY());
        }
    }
    int index = this->white_drts.size() - 1;

    if (this->white_drts.size() > board_.white_drts.size()) { // w raziek kiedy pierwotna tablica jest za duza niz skopiowana
        this->removeDraught(this->white_drts[index].getX(), this->white_drts[index].getY());
        index--;
    }
    
    for (int i = 0; i < black_drts.size(); i++) {

        if (i >= this->black_drts.size()) {  // jesli tablica pierwotna jest za mala
            Elements elem;

            elem.setElem(board_.black_drts[i].getElem());
            elem.setX(board_.black_drts[i].getX());
            elem.setY(board_.black_drts[i].getY());

            this->black_drts.push_back(elem);
        }
        else {
            this->black_drts[i].setElem(black_drts[i].getElem());
            this->black_drts[i].setX(black_drts[i].getX());
            this->black_drts[i].setY(black_drts[i].getY());
        } 
    }
    
    index = this->black_drts.size() - 1;

    if (this->black_drts.size() > board_.black_drts.size()) { // w raziek kiedy pierwotna tablica jest za duza niz skopiowana
        this->removeDraught(this->black_drts[index].getX(), this->black_drts[index].getY());
        index--;
    }

    return *this;
}

void Board::initBoard() {
    Elements element; int indexB = 0, indexW = 0;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
            if (j % 2 == 0) {
                if (i % 2 == 0) this->board[i][j] = WhiteField;
                else {
                    this->board[i][j] = BlackDraught;
                    element.setElem(BlackDraught);
                    element.setX(i); element.setY(j);
                    black_drts.push_back(element);

                    this->board_black_drs[indexB] = element;
                    indexB++;
                }
            }
            else {
                if (i % 2 == 0) {
                    this->board[i][j] = BlackDraught;
                    element.setElem(BlackDraught);
                    element.setX(i); element.setY(j);
                    black_drts.push_back(element);

                    this->board_black_drs[indexB] = element;
                    indexB++;   

                }
                else this->board[i][j] = WhiteField;
            }
        }
    }

    for (int j = 3; j < 5; j++) {
        for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
            if (j % 2 == 0) {
                if (i % 2 == 0) this->board[i][j] = WhiteField;
                else this->board[i][j] = BlackField;
            }
            else {
                if (i % 2 == 0) this->board[i][j] = BlackField;
                else this->board[i][j] = WhiteField;
            }
        }
    }

    for (int j = 5; j < AMOUNT_OF_FIELDS; j++) {
        for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
            if (j % 2 == 0) {
                if (i % 2 == 0) this->board[i][j] = WhiteField;
                else {
                    this->board[i][j] = WhiteDraught;
                    element.setElem(WhiteDraught);
                    element.setX(i); element.setY(j);
                    white_drts.push_back(element);
                }
            }
            else {
                if (i % 2 == 0) {
                    this->board[i][j] = WhiteDraught;
                    element.setElem(WhiteDraught);
                    element.setX(i); element.setY(j);
                    white_drts.push_back(element);
                }
                else this->board[i][j] = WhiteField;
            }
        }
    }
}
void Board::movementBoard(int drt, int x1, int y1, int x2, int y2) {
    int pom = 0;
    pom = this->board[x1][y1];
    this->board[x1][y1] = this->board[x2][y2];
    this->board[x2][y2] = pom;
    
    if (pom == WhiteDraught || pom == WhiteKing) {
        this->moveWhiteDraught(drt, x2, y2);
    }
    else { 
        this->moveBlackDraught(drt, x2, y2);
    }

}

void Board::moveWhiteDraught(int drt, int x2, int y2) {
   this->white_drts[drt].setX(x2);
   this->white_drts[drt].setY(y2);
}

void Board::moveBlackDraught(int drt, int x2, int y2) {

   this->black_drts[drt].setX(x2);
   this->black_drts[drt].setY(y2);
}

void Board::showBoard() {
    std::cout << "================================= " << std::endl;
    for (int j = 0; j < AMOUNT_OF_FIELDS; j++) {
        for (int i = 0; i < AMOUNT_OF_FIELDS; i++) {
            if (this->board[i][j] == BlackDraught) std::cout << "|  x  ";
            else if (this->board[i][j] == WhiteDraught) std::cout << "|  o  ";
            else if (this->board[i][j] == WhiteField) std::cout << "|     ";
            else if (this->board[i][j] == BlackField) std::cout << "||||||";
            else std::cout << this->board[i][j] << "    "; 
        }
        std::cout << "|";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;
    }
}

int Board::getPosition(int x, int y) {
    return this->board[x][y];
}

// change to king
void Board::setPosition(int drt, int x, int y, int draught) {
    this->board[x][y] = draught;
    
    if (draught == BlackKing) this->black_drts[drt].setElem(draught);
    else this->white_drts[drt].setElem(draught);
}

void Board::removeDraught(int x, int y) {
    
    std::vector<Elements>::iterator it;
    
    if (this->getPosition(x, y) == BlackDraught || this->getPosition(x, y) == BlackKing) {
        for (int i = 0; i < this->black_drts.size(); i++) {
            if (this->black_drts[i].getX() == x && this->black_drts[i].getY() == y) {
                it = this->black_drts.begin();
                for (int j = 0; j < i; j++) {
                    it++;
                }
                this->black_drts.erase(it);
                this->board[x][y] = BlackField;
                return;
            }
        }
    }
    else {
        for (int i = 0; i < this->white_drts.size(); i++) {
            if (this->white_drts[i].getX() == x && this->white_drts[i].getY() == y) {
                it = this->white_drts.begin();
                for (int j = 0; j < i; j++) {
                    it++;
                }
                this->white_drts.erase(it);
                this->board[x][y] = BlackField;
                return;
            }
        }
    } 
}

void Board::addWPoint() {
    this->points_white++;
}

void Board::addBPoint() {
    this->points_black++;
}

int Board::getWPoints() {
    return this->points_white;
}

int Board::getBPoints() {
    return this->points_black;
}

int Board::getBlackDraught() {
    return this->black_drts.size();
}

int Board::getWhiteDraugth() {
    return this->white_drts.size();
}

int Board::checkVictory() {
    // vicotry of White draught
    if (this->points_white == AMOUNT_OF_DRAUGHTS) return 0;
    // victory of Black draught
    else if (this->points_black == AMOUNT_OF_DRAUGHTS) return 1; 
    // 2 means remis
    else return -1;
}

// checking 

bool Board::checkBlackField(int x, int y) {
    if (this->board[x][y] == BlackField) return true;
    else return false;
}

bool Board::checkPositionAbroad(int x2, int y2) {
    return (x2 < 8 && x2 >= 0) && (y2 < 8 && y2 >= 0);
}

int Board::checkDirection(int x1, int y1, int x2, int y2, int draught) {

    int distance_x = x2 - x1;
    int distance_y = y2 - y1;

    // check the capturing
    if (abs(distance_x) == 2) {
        return this->checkCapturing(x1, y1, distance_x, distance_y, draught);
    }

    if (draught == WhiteDraught) {
        if ((distance_x == 1 && distance_y == -1) || (distance_x == -1 && distance_y == -1)) {
            if (y2 < 2) return fourth_level;
            else if (y2 < 4) return third_level;
            else if(y2 < 6) return second_level;
            else if (y2 < 8) return first_level;
        }
        else return 0;
    }
    else if (draught == BlackDraught) {
        if ((distance_x == -1 && distance_y == 1) || (distance_x == 1 && distance_y == 1)) {
            if (y2 < 2) return first_level;
            else if (y2 < 4) return second_level;
            else if (y2 < 6) return third_level;
            else if (y2 < 8) return fourth_level;
        }
        else return 0;
    }   
}

int Board::checkCapturing(int x1, int y1, int distance_x, int distance_y, int draught) {

    int x = x1 + distance_x/2;
    int y = y1 + distance_y/2;
   
    if (draught == BlackDraught) {
        if (this->board[x][y] == WhiteDraught) {
            this->removeDraught(x, y);
            return capturing_draught;
        }
        else return 0;
    }    
    else {
        if (this->board[x][y] == BlackDraught) {
            return capturing_draught;
        }
        else return 0;
    }
}




