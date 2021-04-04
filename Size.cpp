#include "Size.h"
using namespace ady;

Size::Size() {
	/**
	Default constructor**/
	width = height = 0;
}

Size::Size(unsigned int w, unsigned int h) {
	/**
	@param - w
	@param - h
	*
	* Parameterized constructor
	**/
	width = w;
	height = h;
}

unsigned int Size::getwidth() {
	/**
	@return returns the width**/
	return width;
}

unsigned int Size::getheight() {
	/**
	@return returns the height**/
	return height;
}