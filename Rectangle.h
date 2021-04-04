#pragma once
#include "Point.h"
#include "oke.h"
class ady::Rectangle
{
public:
	Rectangle();
	Rectangle(int x1, int y1, unsigned  int width1, unsigned int height1);
	Rectangle(Point topleft, Point botright);

	int getx();
	int gety();
	unsigned int getwidth();
	unsigned int getheight();
	void setx(int r);
	void sety(int r);
	void setwidth(unsigned int r);
	void setheight(unsigned int r);

	Rectangle operator&(const Rectangle& other);
	Rectangle operator|(const Rectangle& other);
	Rectangle operator+(Point& p);
	Rectangle operator-(Point& p);

	friend std::ostream& operator<<(std::ostream& os, Rectangle& p);
	friend std::istream& operator>>(std::istream& os, Rectangle& p);
private:
	int x, y;
	unsigned int width, height;
};

