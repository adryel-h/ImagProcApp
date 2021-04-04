#pragma once
#include "oke.h"

class ady::Size
{
public:
	Size();
	Size(unsigned int width, unsigned int height);
	unsigned int getwidth();
	unsigned int getheight();
private:
	unsigned int width, height;
};

