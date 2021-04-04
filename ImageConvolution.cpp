#include "ImageConvolution.h"
#include <utility>

int movx[9] = { -1,-1,-1,0,0,0,1,1,1 };
int movy[9] = { -1,0,1,-1,0,1,-1,0,1 };

int ImageConvolution::csp(Image& src, int x, int y) {
	/**
	@param - src
	@param - x
	@param - y
	*
	* This function computes the sum that will represent the new value of the pixel (x,y) after applying the kernel to it
	* @return Returns the resulted sum
	**/
	int sum = 0, i2 = 0, j2 = 0;
	for (int i = 0; i < 9; i++) {
		if (j2 == 3) {
			j2 = 0;
			i2++;
		}
		sum += src.refpixel(x + movx[i], y + movy[i]) * kernel[i2][j2];
		j2++;
	}
	return sum;
}

void ImageConvolution::transform() {
	/**
	* This function takes the kernel and flips it along it's horizontal and vertical axis
	**/
	int aux;
	for (int i = 0; i < 3; i++) {
		aux = kernel[0][i];
		kernel[0][i] = kernel[2][i];
		kernel[2][i] = aux;
	}
	for (int i = 0; i < 3; i++) {
		aux = kernel[i][0];
		kernel[i][0] = kernel[i][2];
		kernel[i][2] = aux;
	}
}

short int ImageConvolution::identity_function(int x) {
	/**
	@param - x
	*
	* Identity function: used for the identity kernel
	* @return Returns x
	**/
	return x;
}

ImageConvolution::ImageConvolution() {
	/**
	* Default constructor
	**/
	kernel[1][1] = 1;
	clip = &identity_function;
}

ImageConvolution::ImageConvolution(int k[3][3], short int (*po)(int)) {
	/**
	@param - k
	@param - po
	*
	* Constructor that takes as paramater a 3x3 matrix that will represent the kernel and a pointer to a function
	**/
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			kernel[i][j] = k[i][j];
	transform();
	clip = po;
}

void ImageConvolution::process(Image& src, Image& dst) {
	/**
	@param - src
	@param - dst
	*
	* This function applies the Convolution to the image srs and saves the result in dst
	* It iterates through each pixels (that's surrounded by sufficient pixels) and calls the csp() function
	* the result get's outputted in [0,255] by the clip() function
	**/
	dst = dst.zeros(src.getwidth(), src.getheight());
	for (int i = 2; i < dst.getheight(); i++) {
		for (int j = 2; j < dst.getwidth(); j++) {
			dst.refpixel(i, j) = clip(csp(src, i, j));
		}
	}
}