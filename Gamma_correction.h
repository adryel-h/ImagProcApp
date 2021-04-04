#pragma once
#include "ImageProcessing.h"
#include "oke.h"
using namespace ady;

class Gamma_correction : public ImageProcessing
{
public:
	Gamma_correction();
	Gamma_correction(float power);
	void process(Image& src, Image& dst);
private:
	float power;
};

