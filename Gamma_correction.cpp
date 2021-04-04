#include "Gamma_correction.h"

Gamma_correction::Gamma_correction() {
	/**
	* Default constructor
	**/
	power = 1;
}

Gamma_correction::Gamma_correction(float coef) {
	/**
	@param - coef
	*
	* Constructor that sets the power to coef
	**/
	power = coef;
}

void Gamma_correction::process(Image& src, Image& dst) {
	/** 
	@param - src
	@param - dst
	*
	*this function creates an Image whose pixels are equal to the pixel's of src raised to the power of 'power'
	* and saves the result in dst
	 **/
	dst.initialize(src.getwidth(), src.getheight());
	for (int i = 1; i <= dst.getheight(); i++)
	{
		for (int j = 1; j <= dst.getwidth(); j++)
		{
			if (src.refpixel(i, j) != 0) {
				if (pow(src.refpixel(i, j), power) > 255)
					dst.refpixel(i, j) = 255;
				else
				{
					if (pow(src.refpixel(i, j), power) < 0)
						dst.refpixel(i, j) = 0;
					else
						dst.refpixel(i, j) = int(pow(src.refpixel(i, j), power));
				}
			}
			else
				dst.refpixel(i, j) = 0;

		}
	}
}