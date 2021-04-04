#include <iostream>
#include <iomanip>
#include "Image.h"
#include "ImageProcessing.h"
#include "BCA.h"
#include "Gamma_correction.h"
#include "ImageConvolution.h"
#include "Point.h"
#include "Rectangle.h"
#include <stdlib.h>
#include <crtdbg.h>
#include "test.h"
#include <cassert>
#include <cstring>
#define _CRTDBG_MAP_ALLOC
#define _CRT_NONSTDC_DEPRECATE
using namespace std;

short int identicfunct(int x) {
	/**
	@param - x
	* @return returns x
    **/
	return x;
}

short int meanfunct(int x) {
	/**
	@param - x
	* @return returns x/9
	**/
	return int(x / 9);
}

short int gaussianfunct(int x) {
	/**
	@param - x
	* @return returns x/16
	**/
	return int(x / 16);
}

short int sobelfunct(int x) {
	/**
	@param - x
	* @return returns (x / 4 + 255) / 2
	**/

	return int((x / 4 + 255) / 2);
}

void testClippers() {
	std::cout << "Testing Clippers\n";
	assert(identicfunct(3) == 3);
	assert(meanfunct(18) == 2);
	assert(gaussianfunct(16) == 1);
	assert(sobelfunct(-4 * 255) == 0);
}

void menu()
{
	cout << "\n Select operation";
	cout << "\n 0. Exit";
	cout << "\n 1. Load an Image";
	cout << "\n 2. Adjust brightness and contrast";
	cout << "\n 3. Gamma correction";
	cout << "\n 4. Image Convolution";
	cout << "\n 5. Draw Circle ";
	cout << "\n 6. Draw Line ";
	cout << "\n 7. Draw Rectangle ";
	cout << "\n 8. Save image ";
}

int main()
{
	{
		int operation;
		int x, y;
		float alpha, beta;
		char name[100], name2[100] = "./sample_images/";

		short int (*p[5])(int x) = { identicfunct, meanfunct, gaussianfunct, sobelfunct };
		int matrix[3][3], select;

		Image player, result;
		BCA bca = {};
		Gamma_correction gc;
		ImageConvolution ic;
		Rectangle rec;
		Point center, first, second;

		do
		{
			menu();
			cout << "\n\nOperation: ";
			cin >> operation;

			switch (operation)
			{
			case 0:
				//exit
				break;
			case 1:
				cout << "\n ** Only enter the image name (No extension/file_type) **\n";
				cin >> name;
				strcat_s(name2, name);
				strcat_s(name2, ".ascii.pgm");
				player.load(name2);
				break;
			case 2:
				cout << "\n Enter contrast and brightness: \n";
				cin >> alpha >> beta;
				bca = BCA{ alpha, beta };
				bca.process(player, result);
				player = result;
				break;
			case 3:
				cout << "\n Enter desired correction: \n";
				float gamma;
				cin >> gamma;
				gc = Gamma_correction{ gamma };
				gc.process(player, result);
				player = result;
				break;
			case 4:
				cout << "\n Enter Kernel \n";

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
						cin >> matrix[i][j];
				}

				cout << "\n Choose clipping function:\n 1. f(x) = x \n 2. f(x) = x/9 \n 3. f(x) = x/16 \n 4. f(x) = (x / 4 + 255) / 2 \n";
				cin >> select;

				ic = ImageConvolution{ matrix, p[select - 1] };
				ic.process(player, result);
				player = result;
				break;
			case 5:
				cout << "\n Enter the coordinates of the center \n";
				int colour, thick;

				cin >> x >> y;
				center = Point{ x, y };

				cout << "\n Enter radius \n";
				cin >> x;
				cout << "\n Enter colour \n";
				cin >> colour;

				if (colour < 0)
					colour = 0;

				cout << "\n Enter thickness - from 0 to 5 \n";
				cin >> thick;

				player.drawCircle(center, x, colour, thick);
				break;
			case 6:
				cout << "\n Enter the coordinates of the first point\n";
				cin >> x >> y;
				first = Point{ x, y };

				cout << "\n Enter the coordinates of the second point \n";
				cin >> x >> y;
				second = Point{ x, y };

				cout << "\n Enter colour \n";
				cin >> x;
				if (x < 0)
					x = 0;
				player.drawLine(first, second, x);
				break;
			case 7:
				cout << "\n Enter the coordinates of the top-left point of the rectangle\n";
				unsigned int wid, hei;
				cin >> x >> y;

				cout << "\n Enter the width and height of the rectangle\n";
				cin >> wid >> hei;

				rec = Rectangle{ x, y, wid, hei };
				cout << "\n Enter colour\n";
				cin >> x;
				if (x < 0)
					x = 0;
				player.drawRectangle(rec, x);
				break;
			case 8:
				player.save("finalresult.pgm");
				cout << "\n Saved!\n";
				break;
			default:
				cout << "\nWrong operation! Try again";
				break;
			}
		} while (operation != 0);

	}

	//testall();
	//testClippers();
	//_CrtDumpMemoryLeaks();
	return 0;
}
