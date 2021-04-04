#include "Point.h"
#include <exception>
using namespace ady;

Point::Point() {
	/** Default constructor that initializes both fields to 0 **/
	x = 0;
	y = 0;
}

Point::Point(int x1, int y1) {
	/**
	@param - x1
	@param - y1
	*
	*Parameterized constructor **/
	x = x1;
	y = y1;
}

int& Point::getx() {
	/** @return returns the x coordinate (the row) **/
	return x;
}

int& Point::gety() {
	/** @return returns the y coordinate (the column) **/
	return y;
}

std::istream& operator>>(std::istream& os, Point& p) {
	/**
	@param - ps
	@param - p
	*
	*A function that overloads the stream extraction operator and updates the atributes of the object
	* @return returns os
	**/
	unsigned int x1, y1;
	os >> x1 >> y1;
	p.getx() = x1;
	p.gety() = y1;
	return os;
}

std::ostream& operator<<(std::ostream& os, Point& p) {
	/**
	@param - os
	@param - p
	*
	* A function that overloads the stream insertion operator and prints the x and y coordinate of the object 
	* @return returns os
	**/
	os << "(" << p.getx() << "," << p.gety() << ")";
	return os;
}