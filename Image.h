#pragma once
#include <iostream>
#include "Point.h"
#include "Rectangle.h"
#include "oke.h"
using namespace std;

class ady::Image
{
public:
	Image();
	Image(unsigned int w, unsigned int h);
	Image(const Image& other);

	~Image();

	unsigned int getwidth();
	unsigned int getheight();

	short int& refpixel(unsigned int x, unsigned int y);
	short int& refpixel(Point po);
	short int* refrow(unsigned int y);

	void clear();
	void initialize(unsigned int width, unsigned int height);

	bool load(std::string imagePath);
	bool save(std::string imagePath);
	bool empty();
	bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	bool nullity();

	Image& operator=(const Image& other);
	Image operator+(const Image& ot);
	Image operator-(const Image& ot);
	Image operator*(const Image& ot);
	Image operator+(unsigned int scalar);
	Image operator-(unsigned int scalar);
	Image operator*(unsigned int scalar);

	void drawCircle(Point center, int radius, unsigned short int colour, unsigned  int thickness);
	void drawLine(Point p1, Point p2, unsigned short int colour);
	void drawRectangle(Rectangle r, unsigned short int colour);
	void drawRectangle(Point tl, Point br, unsigned short int colour);

	friend std::ostream& operator<<(std::ostream& os, Image& dt);

	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);
	static float distance(Point& p1, Point& p2);
	static float line(Point& p1, Point& p2, Point& q);
private:
	short int** m_data;
	unsigned int m_width;
	unsigned int m_height;
};
