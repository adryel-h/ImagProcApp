#pragma once
#include <iostream>
#include "oke.h"
using namespace std;

class ady::Point
{
public:
	Point();
	Point(int x, int y);

	friend std::ostream& operator<<(std::ostream& os, Point& p);
	friend std::istream& operator>>(std::istream& os, Point& p);

	int& getx();
	int& gety();

private:
	int x, y;
};
