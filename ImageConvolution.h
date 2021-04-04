#pragma once
#include "ImageProcessing.h"
#include "oke.h"
using namespace ady;

class ImageConvolution : public ImageProcessing
{
public:
	ImageConvolution();
	ImageConvolution(int k[3][3], short int (*po)(int));

	void process(Image& src, Image& dst);
	void transform();

	int csp(Image& src, int x, int y);

	static short int identity_function(int x);
private:
	int kernel[3][3] = { 0 };
	short int (*clip)(int);
};

