#pragma once
#include <iostream>

class Elements
{
	int elem;
	int x;
	int y;

public:
	Elements() {};
	~Elements() {};
	inline int getElem() { return this->elem; }
	inline int getX() { return this->x; }
	inline int getY() { return this->y; }
	
	inline void setElem(int ELEM) { this->elem = ELEM; }
	inline void setX(int X) { this->x = X; }
	inline void setY(int Y) { this->y = Y; }
};
