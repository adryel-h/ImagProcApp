#include "Image.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <math.h>
using namespace std;
using namespace ady;

Image::Image() {
	/**
	* Default constructor of Image
	**/
	m_width = 0;
	m_height = 0;
	m_data = nullptr;
}

Image::Image(unsigned int w, unsigned int h) {
	/**
	@param - w
	@param - h
	* 
	*Constructor of Image that assignes values to width and height
	*Prepares a matrix of the corresponding size **/
	m_width = w;
	m_height = h;
	m_data = new short int* [h + 1];
	for (int i = 1; i <= h; i++)
	{
		m_data[i] = new short int[w + 1];
	}
}

Image::Image(const Image& other) {
	/**
	@param - other
	*
	* Copy constructor that creates an instance of Image and copies the information of the other image inside it
	**/
	m_height = other.m_height;
	m_width = other.m_width;
	m_data = new short int* [m_height + 1];
	for (int i = 1; i <= m_height; i++)
	{
		m_data[i] = new short int[m_width + 1];
		for (int j = 1; j <= m_width; j++)
			m_data[i][j] = other.m_data[i][j];
	}
}

unsigned int Image::getwidth() {
	/** Getter for the width **/
	return m_width;
}

unsigned int Image::getheight() {
	/** Getter for the height **/
	return m_height;
}

short int& Image::refpixel(unsigned int x, unsigned int y) {
	/**
	@param - x
	@param - y
	*
	@return Returns a reference to the pixel at the coord (x,y) **/
	if (x > m_height || y > m_width || x == 0 || y == 0)
	{
		throw exception();
	}
	else
		return  m_data[x][y];
}

short int& Image::refpixel(Point po) {
	/** 
	@param - po
	*
	@return a reference to the pixel at the coord (x,y) using the Point class **/
	if (po.getx() > m_height || po.gety() > m_width || po.getx() == 0 || po.gety() == 0)
		throw exception();
	else
		return m_data[po.getx()][po.gety()];
}

short int* Image::refrow(unsigned int y) {
	/** 
	@param - y 
	* 
	@return Returns the address of the y'th row in the image **/
	if (y == 0 || y > m_height)
		throw exception();
	else
		return m_data[y];
}

void Image::initialize(unsigned int wid, unsigned int hei) {
	/**
	@param - width
	@param - height
	* 
	* Will preapare the Image object for a picture having the specified dimensions by releasing the current matrix and
	*constructing one of appropriate size **/
	clear();
	this->m_width = wid;
	this->m_height = hei;
	m_data = new short int* [hei + 1];
	for (int i = 1; i <= hei; i++)
	{
		m_data[i] = new short int[wid + 1];
	}
}

void Image::clear() {
	/** A function that releases the matrix of the Image **/
	for (int i = 1; i <= m_height; i++) {
		delete[] m_data[i];
	}
	if (m_height != 0)
		delete[] m_data;
	m_width = m_height = 0;
	m_data = nullptr;
}

bool Image::load(std::string imagePath) {
	/**
	@param - imagePath
	* 
	*A function that loads a picture from a file into an image object
	@return Returns true or false depending on the success or lack thereof the operation **/
	ifstream f;
	f.open(imagePath);
	unsigned int  b = 0, c = 0, max = 0;
	char s[10];
	f >> s >> b >> c >> max;
	initialize(b, c);
	for (int i = 1; i <= m_height; i++)
		for (int j = 1; j <= m_width; j++) {
			f >> m_data[i][j];
		}
	f.close();
	return true;
}

bool Image::save(std::string imagePath) {
	/**
	@param - imagePath
	* 
	* A function that saves the stored picture in the Image object into a file
	 @return Returns true or false depending on the success or lack thereof the operation **/
	ofstream g(imagePath);
	g << "P2" << "\n";
	g << m_width << " " << m_height << "\n";
	g << 255 << "\n";
	for (int i = 1; i <= m_height; i++) {
		for (int j = 1; j <= m_width; j++)
			g << m_data[i][j] << " ";
		g << "\n";
	}
	g.close();
	return true;
}

bool Image::empty() {
	/** 
	*  An image is considered emtpy when all of the pixels have the same value
	*@return  This function returns true if the image is empty
	 **/
	if (m_data == NULL)
		throw exception();
	else {
		int y = m_data[1][1], okay = 1;
		for (int i = 1; i <= m_height && okay; i++)
		{
			for (int j = 1; j <= m_width && okay; j++)
				if (m_data[i][j] != y)
					okay = 0;
		}
		if (okay)
			return true;
		else return false;
	}
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	/**
	@param - roiImg
	@param - x
	@param - y
	@param - width
	@param - height
	*
	*  This function modifies roiImg such that it represents the specified portion of the original image
	* @return Returns true if operation was succesful 
	**/
	if (x + width - 1 > m_width || y + height - 1 > m_height || x == 0 || y == 0)
		throw exception();
	else
	{
		roiImg.initialize(width, height);
		int i1 = 1, j1 = 1;
		for (int i = y; i < height + y; i++)
		{
			short int* auxm = *(m_data + i);
			short int* auxr = *(roiImg.m_data + i1);
			j1 = 1;
			for (int j = x; j < x + width; j++)
			{
				*(auxr + j1) = *(auxm + j);
				j1++;
			}
			i1++;
		}
	}
	return true;
}

bool Image::nullity() {
	/** 
	@return This function returns true if the object has no image**/
	if (m_data == nullptr)
		return true;
	else return false;
}

Image& Image::operator=(const Image& other) {
	/**
	@param - other
	* 
	*It will initially release the matrix of the current Image and afterwards it will construct
	*the picture from 'other' into the current image 
	 @return Returns the image object **/
	clear();
	m_height = other.m_height;
	m_width = other.m_width;
	m_data = new short int* [m_height + 1];
	for (int i = 1; i <= m_height; i++)
	{
		m_data[i] = new short int[m_width + 1];
		for (int j = 1; j <= m_width; j++)
			m_data[i][j] = other.m_data[i][j];
	}
	return *this;
}

Image Image::operator+(const Image& ot) {
	/**
	@param - ot 
	* 
	* Function that adds two images together (element-wise)
	* @return returns the resulted image **/
	if (m_width != ot.m_width || m_height != ot.m_height)
		throw exception();
	else
	{
		for (int i = 1; i <= m_height; i++) {
			for (int j = 1; j <= m_width; j++) {
				m_data[i][j] += ot.m_data[i][j];
				if (m_data[i][j] > 255)
					m_data[i][j] = 255;
			}
		}
	}
	return *this;
}

Image Image::operator-(const Image& ot) {
	/**
	@param - ot
	*
	*  Function that substracts an image from another image (element wise)
	* @return returns the resulted image **/
	if (m_width != ot.m_width || m_height != ot.m_height)
		throw exception();
	else {
		for (int i = 1; i <= m_height; i++) {
			for (int j = 1; j <= m_width; j++) {
				m_data[i][j] -= ot.m_data[i][j];
				if (m_data[i][j] < 0)
					m_data[i][j] = 0;
			}
		}
	}
	return *this;
}

Image Image::operator*(const Image& ot) {
	/**
	@param - ot
	* 
	* Function that multiplies one image with another (element-wise)
	* @return returns the resulted image **/
	if (m_width != ot.m_width || m_height != ot.m_height)
		throw exception();
	else {
		for (int i = 1; i <= m_height; i++) {
			for (int j = 1; j <= m_width; j++) {
				m_data[i][j] *= ot.m_data[i][j];
				if (m_data[i][j] > 255)
					m_data[i][j] = 255;
			}
		}
	}
	return *this;
}

Image Image::operator+(unsigned int scalar) {
	/** 
	@param - scalar
	*
	*  Function that adds a scalar to the image (element-wise)
	* @return returns the resulted image
	**/
	for (int i = 1; i <= m_height; i++) {
		for (int j = 1; j <= m_width; j++) {
			m_data[i][j] += scalar;
			if (m_data[i][j] > 255)
				m_data[i][j] = 255;
		}
	}
	return *this;
}

Image Image::operator-(unsigned int scalar) {
	/**
	@param - scalar
	* 
	* Function that substracts the image by a scalar (element-wise)
	* @return returns the resulted image
	**/
	for (int i = 1; i <= m_height; i++) {
		for (int j = 1; j <= m_width; j++) {
			m_data[i][j] -= scalar;
			if (m_data[i][j] < 0)
				m_data[i][j] = 0;
		}
	}
	return *this;
}

Image Image::operator*(unsigned int scalar) {
	/**
	@param - scalar
	* 
	* Function that multiplies by a scalar an image (element-wise)
	* @return returns the resulted image
	**/
	for (int i = 1; i <= m_height; i++) {
		for (int j = 1; j <= m_width; j++) {
			m_data[i][j] *= scalar;
			if (m_data[i][j] > 255)
				m_data[i][j] = 255;
		}
	}
	return *this;
}

void Image::drawCircle(Point center, int radius, unsigned short int colour, unsigned int thickness) {
	/**
	@param - center
	@param - radius
	@param - colour
	@param - thickness
	* 
	* This function draws a circle with the given colour on the Image of the object having the given center with the given radius 
	* I also implemented a thickness option that has 5 intensities **/
	if (colour > 255)
		colour = 255;
	if (thickness > 5)
		thickness = 5;
	float thick = thickness;
	float rad = radius;
	for (int i = 1; i <= m_height; i++) {
		for (int j = 1; j <= m_width; j++) {
			Point aux{ i,j };
			if (-0.5 - thick / 10 <= distance(aux, center) - rad && distance(aux, center) - rad <= 0.7 + thick / 10) {
				refpixel(aux) = colour;
			}
		}
	}
}

void Image::drawLine(Point p1, Point p2, unsigned short int colour) {
	/**
	@param - p1
	@param - p2
	@param - colour
	*
	*This function draws a line determined by the two given points on the image of the object having given colour **/
	if (colour > 255)
		throw exception();
	if (p1.getx() == p2.getx()) {
		int xx = p1.getx();
		for (int i = 1; i <= m_width; i++)
			refpixel(xx, i) = colour;
	}
	else {
		if (p1.gety() == p2.gety()) {
			int yy = p1.gety();
			for (int i = 1; i <= m_height; i++)
				refpixel(i, yy) = colour;
		}
		else {
			for (int i = 1; i <= m_height; i++) {
				for (int j = 1; j <= m_width; j++) {
					Point q{ i,j };
					if (-150 <= line(p1, p2, q) && line(p1, p2, q) <= 150) {
						refpixel(q) = colour;
					}

				}
			}
		}
	}
}

void Image::drawRectangle(Rectangle r, unsigned short int colour) {
	/**
	@param - r
	@param - colour
	*
	* This function draws the Rectangle r onto the image of the object **/
	int cap = r.gety() + r.getwidth(), cap2 = r.getx() + r.getheight(), m_h = m_height, m_w = m_width, r_h = r.getheight(), r_w = r.getwidth();
	if (r.getx() <= 0 || r.getx() > m_height || r.gety() <= 0 || r.gety() > m_width)
		throw exception();
	if (m_w - (r.gety() + r_w) < 0)
		cap = m_width;
	if (m_h - (r.getx() + r_h) < 0)
		cap2 = m_height;
	for (int i = r.gety(); i <= cap; i++) {
		refpixel(r.getx(), i) = colour;
		refpixel(cap2, i) = colour;
	}
	for (int i = r.getx(); i <= cap2; i++) {
		refpixel(i, r.gety()) = refpixel(i, cap) = colour;
	}
}

void Image::drawRectangle(Point tl, Point br, unsigned short int colour) {
	/**
	@param - tl
	@param - br
	@param - colour
	*
	*This function draws the Rectangle r onto the image of the object **/
	Rectangle r{ tl, br };
	drawRectangle(r, colour);
}

std::ostream& operator<<(std::ostream& os, Image& dt) {
	/**
	@param - os
	@param - dt
	* 
	*A function that overloads the stream insertion operator << and prints out the values contained in the matrix of the
	*image object
	* @return returns os **/
	os << "Width: " << dt.getwidth() << " Height: " << dt.getheight() << "\n\n";
	for (int i = 1; i <= dt.getheight(); i++) {
		for (int j = 1; j <= dt.getwidth(); j++)
			os << setw(3) << dt.refpixel(i, j) << " ";
		os << "\n";
	}
	os << "\n";
	return os;
}

Image Image::zeros(unsigned int width, unsigned int height) {
	/**
	@param - width
	@param - height
	* 
	* @return Returns an image of specified dimensions filled with zeros **/
	Image result{ width, height };
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++)
			result.m_data[i][j] = 0;
	}
	return result;
}

Image Image::ones(unsigned int width, unsigned int height) {
	/**
	@param - width
	@param - height
	*
	* @return Returns an image of specified dimensions filled with ones **/
	Image result{ width, height };
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++)
			result.m_data[i][j] = 1;
	}
	return result;
}

float Image::distance(Point& p1, Point& p2) {
	/**
	@param - p1
	@param - p2
	*
	*  @return Returns the distance between p1 and p2
	**/
	return sqrt(pow(p1.getx() - p2.getx(), 2) + pow(p1.gety() - p2.gety(), 2));
}

float Image::line(Point& p1, Point& p2, Point& q) {
	/**
	@param - p1
	@param - p2
	@param - q
	*
	* @return Returns the value of the equation of a line determined by p1 and p2 evaluated at q
	**/
	float a = p1.getx(), b = p1.gety(), c = p2.getx(), d = p2.gety(), x = q.getx(), y = q.gety();
	return (x * (d - b) + y * (a - c) - d * a + b * a + b * c - b * a);
}

Image::~Image() {
	/** the destructor of the class Image, It releases the memory allocated for the matrix **/
	clear();
}