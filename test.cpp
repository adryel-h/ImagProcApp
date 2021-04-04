#include "test.h"
#include <iostream>
#include "Image.h"
#include <cassert>
#include <exception>
#include "BCA.h"
#include "Gamma_correction.h"
#include "ImageConvolution.h"
#include "Size.h"
using namespace std;
using namespace ady;

void testimage() {
	std::cout << "Testing Image\n";
	Image ob, ob2{ 3,4 }, ob3{ ob2 }, im;
	assert(ob.getheight() == 0);
	assert(ob.getwidth() == 0);
	assert(ob2.getwidth() == 3);
	assert(ob2.getheight() == 4);
	assert(ob3.getwidth() == 3);
	assert(ob3.getheight() == 4);
	assert(ob.nullity() == true);
	im.load("testimage.ascii.pgm");
	assert(im.refpixel(1, 2) == 2);
	short int* po = im.refrow(3);
	assert(*(po + 1) == im.refpixel(3, 1));
	im.clear();
	assert(im.getheight() == 0);
	assert(im.nullity() == true);
	ob.initialize(5, 5);
	assert(ob.getheight() == 5);
	assert(ob.nullity() == false);
	assert(ob.empty() == true);
	im.load("testimage.ascii.pgm");
	im.save("savetest.pgm");
	im.getROI(ob, 2, 2, 2, 2);
	assert(ob.getwidth() == 2);
	assert(ob.refpixel(1, 2) == 1);
	assert(ob.refpixel(2, 1) == 1);
	ob = im;
	assert(ob.getwidth() == 3);
	assert(ob.refpixel(1, 1) == 1);
	ob = ob + im;
	assert(ob.refpixel(1, 1) == 2);
	ob = ob - im;
	assert(ob.refpixel(1, 1) == 1);
	ob = ob * im;
	assert(ob.refpixel(2, 2) == 9);
	ob = ob - 3;
	assert(ob.refpixel(2, 2) == 6);
	ob = ob + 3;
	assert(ob.refpixel(2, 2) == 9);
	ob = ob * 0;
	assert(ob.refpixel(1, 3) == 0);
	ob.drawLine(Point(2, 1), Point(2, 3), 40);
	assert(ob.refpixel(2, 2) == 40);
	ob.drawLine(Point(3, 1), Point(1, 3), 11);
	assert(ob.refpixel(2, 2) == 11);
	ob.drawLine(Point(1, 1), Point(3, 1), 24);
	assert(ob.refpixel(2, 1) == 24);
	ob.drawRectangle(Point(1, 1), Point(3, 3), 100);
	assert(ob.refpixel(1, 2) == 100);
	ob.drawCircle(Point(2, 2), 1, 267, 1);
	assert(ob.refpixel(1, 2) == 255);
	ob2 = ob2.zeros(23, 12);
	assert(ob2.refpixel(10, 10) == 0);
	ob2 = ob2.ones(12, 1);
	assert(ob2.refpixel(1, 1) == 1);
	Point a(1, 1), b(2, 2), c(3, 3);
	double result = ob2.distance(a, b);
	assert(int(result) == int(sqrt(2)));
	result = ob2.line(a, b, c);
	assert(result == 0);
}

void testBCA() {
	std::cout << "Testing BCA\n";
	Image ob, result;
	ob.load("testimage.ascii.pgm");
	BCA apply1{ 1.5, 2 }, apply2{ -2,1 }, apply3;
	apply1.process(ob, result);
	assert(result.refpixel(1, 1) == 3);
	apply2.process(ob, result);
	assert(result.refpixel(1, 1) == 0);
	apply3.process(ob, result);
	assert(result.refpixel(1, 1) == 1);
}

void testGamma() {
	Gamma_correction lam, tst{ 2 };
	Image ob, result;
	ob.load("testimage.ascii.pgm");
	lam.process(ob, result);
	assert(result.refpixel(1, 2) == 2);
	tst.process(ob, result);
	assert(result.refpixel(1, 2) == 4);
}

short int meanfunctt(int x) {
	return int(x / 9);
}

void testConv() {
	std::cout << "Testing Convolution\n";
	Image ob, result;
	ob.load("testimage.ascii.pgm");
	ImageConvolution nothing;
	nothing.process(ob, result);
	assert(result.refpixel(2, 2) == 3);
	int matrix[3][3];
	matrix[0][0] = matrix[0][1] = matrix[0][2] = matrix[1][0] = matrix[1][1] = matrix[1][2] = matrix[2][0] = matrix[2][1] = matrix[2][2] = 1;
	ImageConvolution ll{ matrix, meanfunctt };
	ll.process(ob, result);
	assert(result.refpixel(2, 2) == 2);
}

void testPoint() {
	std::cout << "Testing Point\n";
	Point a, b(3, 4);
	assert(a.getx() == 0);
	assert(a.gety() == 0);
	assert(b.getx() == 3);
	assert(b.gety() == 4);
}

void testRectangle() {
	std::cout << "Testing Rectangle\n";
	Rectangle a, b(1, 1, 2, 2), c(Point(1, 1), Point(3, 3));
	assert(a.getheight() == 0);
	assert(a.getx() == 0);
	assert(b.gety() == 1);
	assert(c.getwidth() == 2);
	a.setx(3);
	a.sety(4);
	a.setwidth(12);
	a.setheight(45);
	assert(a.getheight() == 45);
	assert(a.getx() == 3);
	assert(a.gety() == 4);
	assert(a.getwidth() == 12);
	Rectangle result = b & c;
	assert(result.getx() == 1);
	assert(result.getwidth() == 2);
	result = a | c;
	assert(result.getx() == 1);
	assert(result.getwidth() == 15);
	Point pd(1, 1);
	result = a + pd;
	assert(result.getx() == 4);
	assert(result.gety() == 5);
	result = a - pd;
	assert(result.getx() == 3);
	assert(result.gety() == 4);
}

void testSize() {
	std::cout << "Testing Size\n";
	Size a, b(23, 12);
	assert(a.getwidth() == 0);
	assert(b.getheight() == 12);
}

void testall() {
	testimage();
	testBCA();
	testGamma();
	testConv();
	testPoint();
	testRectangle();
	testSize();

}