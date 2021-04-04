#include "Rectangle.h"
using namespace std;
using namespace ady;
Rectangle::Rectangle() {
	/** default constructor **/
	x = y = width = height = 0;
}

Rectangle::Rectangle(int x1, int y1, unsigned int width1, unsigned int height1) {
	/**
	@param - x1
	@param - y1
	@param - width1
	@param - height1
	*
	* parameterized constructor **/
	x = x1;
	y = y1;
	width = width1;
	height = height1;
}

Rectangle::Rectangle(Point topleft, Point botright) {
	/**
	@param - topleft
	@param - botright
	*
	* constructor using two points**/
	x = topleft.getx();
	y = topleft.gety();
	width = botright.gety() - y;
	height = botright.getx() - x;
}

int Rectangle::getx() {
	/** @return returns x **/
	return x;
}

int Rectangle::gety() {
	/** @return returns y**/
	return y;
}

unsigned int Rectangle::getwidth() {
	/** @return returns the width**/
	return width;
}

unsigned int Rectangle::getheight() {
	/** @return returns the height**/
	return height;
}

Rectangle Rectangle::operator|(const Rectangle& other) {
	/** 
	@param -other
	*
	* This function takes as paramter another rectangle and computes it's union with the main rectangle
	* 
	* @return The function returns the minimum rectangle such that both of the rectangles are included in it
	* 
	*  In the first part, I compute the biggest difference between the x coordinates of the rectangles/y coordinates
	* With this I find the height and width of the Union rectangle
	* In the second part I find the top-left point of the union rectangle by comparing the position of the top-left point of the other rectangle
	* to the top-left point of the main rectangle 
	**/
	Rectangle result;
	int set[4] = { x, x + height, other.x, other.x + other.height }, aux;
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++)
			if (set[i] > set[j]) {
				aux = set[i];
				set[i] = set[j];
				set[j] = aux;
			}
	}
	result.height = set[3] - set[0];
	set[0] = y;
	set[1] = y + width;
	set[2] = other.y;
	set[3] = other.y + other.width;
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++)
			if (set[i] > set[j]) {
				aux = set[i];
				set[i] = set[j];
				set[j] = aux;
			}
	}
	result.width = set[3] - set[0];

	if (other.x >= x && other.y >= y) {
		result.x = x;
		result.y = y;
	}
	else {
		if (other.x <= x && other.y >= y) {
			result.x = other.x;
			result.y = y;
		}
		else {
			if (other.x <= x && other.y <= y) {
				result.x = other.x;
				result.y = other.y;
			}
			else {
				result.x = x;
				result.y = other.y;
			}
		}
	}
	return result;
}
Rectangle Rectangle::operator&(const Rectangle& other) {
	/** 
	@param - other
	*
	* This function takes as paramater another rectangle and computes it's intersection with the main rectangle
	* 
	*@return The function returns a rectangle representing their intersection
	* 
	*  The first part of the code computes the width and height of the intersected rectangle, if either of them doesn't exist
	*it returns the null rectangle **/
	int frecv[2] = { 0 };
	pair <int, int> set[4], aux;
	Rectangle result;
	set[0] = { x,0 };
	set[1] = { x + height,0 };
	set[2] = { other.x,1 };
	set[3] = { other.x + other.height,1 };
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++)
			if (set[i].first > set[j].first) {
				aux = set[i];
				set[i] = set[j];
				set[j] = aux;
			}
	}
	for (int i = 0; i < 3; i++) {
		frecv[set[i].second] = frecv[set[i].second] ^ 1;
		if (frecv[set[i].second] == 0) {
			int a = set[i].second ^ 1;
			if (frecv[a] == 0) {
				return result;
			}
		}
	}
	frecv[set[3].second] = frecv[set[3].second] ^ 1;
	result.height = set[2].first - set[1].first;

	set[0] = { y,0 };
	set[1] = { y + width,0 };
	set[2] = { other.y,1 };
	set[3] = { other.y + other.width,1 };

	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 4; j++)
			if (set[i].first > set[j].first) {
				aux = set[i];
				set[i] = set[j];
				set[j] = aux;
			}
	}
	for (int i = 0; i < 3; i++) {
		frecv[set[i].second] = frecv[set[i].second] ^ 1;
		if (frecv[set[i].second] == 0) {
			int a = set[i].second ^ 1;
			if (frecv[a] == 0) {
				result.height = 0;
				return result;
			}
		}
	}
	/**If the algorithm passes to the second part, we know for sure there exists a rectangle so here we compute the location of the top-left 
	 point of the intersection of the rectangles **/
	result.width = set[2].first - set[1].first;
	if (other.x >= x && other.y >= y) {
		result.x = other.x;
		result.y = other.y;
	}
	else {
		if (other.x <= x && other.y >= y) {
			result.x = x;
			result.y = other.y;
		}
		else {
			if (other.x <= x && other.y <= y) {
				result.x = x;
				result.y = y;
			}
			else {
				result.x = other.x;
				result.y = y;
			}
		}
	}
	return result;
}

Rectangle Rectangle::operator+(Point& p) {
	/**
	@param p
	*
	* This function adds the point p to the top-left point of our rectangle
	* @return returns the resulted rectangle **/
	x += p.getx();
	y += p.gety();
	return *this;
}

Rectangle Rectangle::operator-(Point& p) {
	/**
	@param - p
	*
	* this function subtracts the point p from the top-left point of our rectangle
	* @return returns the resulted rectangle **/
	x -= p.getx();
	y -= p.gety();
	return *this;
}

std::ostream& operator<<(std::ostream& os, Rectangle& p) {
	/**
	@param - os
	@param - p
	*
	* A function that overloads the stream insertion operator and prints the atributes of the rectangle **/
	os << "Rectangle: top-left point: (" << p.getx() << "," << p.gety() << "), width: " << p.getwidth() << ", height: " << p.getheight();
	return os;
}

std::istream& operator>>(std::istream& os, Rectangle& p) {
	/**
	@param - os
	@param - p
	*
	* A function that overloads the stream extraction operator and updates the atributes of the object **/
	int a, b;
	unsigned int c, d;
	cout << "Top-left point: ";
	os >> a >> b;
	p.setx(a);
	p.sety(b);
	cout << "Width: ";
	os >> c;
	cout << "Height: ";
	os >> d;
	p.setwidth(c);
	p.setheight(d);
	return os;
}

void Rectangle::setx(int r) {
	/**
	@param - r
	*
	* Sets the value of x to r
	**/
	this->x = r;
}

void Rectangle::sety(int r) {
	/**
	@param - r
	*
	* Sets the value of y to r
	**/
	this->y = r;
}

void Rectangle::setwidth(unsigned int r) {
	/**
	@param - r
	*
	* Sets the value of width to r
	**/
	this->width = r;
}

void Rectangle::setheight(unsigned int r) {
	/**
	@param - r
	*
	* Sets the value of height to r
	**/
	this->height = r;
}