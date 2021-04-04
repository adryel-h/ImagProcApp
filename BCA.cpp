#include "BCA.h"

BCA::BCA() {
	/**
	* Default constructor
	**/
	alfa = 1;
	beta = 0;
}

BCA::BCA(float alfa1, float beta1) {
	/** 
	 @param- alfa1
	*@param- beta1
	* 
	*  Constructor that sets the values of alfa and beta
	* 
	**/
	alfa = alfa1;
	beta = beta1;
}

void BCA::process(Image& src, Image& dst) {
	/**
	@param - src
	@param - dst

	* This function applies the contrast and brightness to src and saves the result in dst
	**/
	dst.initialize(src.getwidth(), src.getheight());
	for (int i = 1; i <= dst.getheight(); i++)
	{
		for (int j = 1; j <= dst.getwidth(); j++) {
			if (alfa * src.refpixel(i, j) + beta > 255)
				dst.refpixel(i, j) = 255;
			else {
				if (alfa * src.refpixel(i, j) + beta < 0)
					dst.refpixel(i, j) = 0;
				else
					dst.refpixel(i, j) = int(alfa * src.refpixel(i, j) + beta);
			}
		}
	}
}