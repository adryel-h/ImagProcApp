#pragma once
#include "ImageProcessing.h"
#include "oke.h"
using namespace ady;
class BCA : public ImageProcessing
{
public:
	BCA();
	BCA(float alfa, float beta);
	void process(Image& src, Image& dst);
private:
	float alfa;
	float beta;
};