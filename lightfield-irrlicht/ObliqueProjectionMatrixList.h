#pragma once

#include <vector>
#include <irrlicht.h>

class ObliqueProjectionMatrixList
{
private:
	double wInScene;
	double hInScene;
	double wByPixel;
	double hByPixel;
	double wBymm;
	double hBymm;
	double tBymm;

	double refractionI;

	std::vector< std::vector<irr::core::matrix4*> > matrixList;

public:
	ObliqueProjectionMatrixList(double widthInScene = 2, double heightInScene =2, int widthByPixel = 20 , int heightByPixel = 20, double widthBymm = 20, double heightBymm = 20, double thicknessBymm = 20, double refractionIndex = 1);
	~ObliqueProjectionMatrixList();
	
	irr::core::matrix4* getProjectionByPixel(int x, int y);
};

