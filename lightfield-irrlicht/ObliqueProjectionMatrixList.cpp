#include "ObliqueProjectionMatrixList.h"
#include <math.h>

ObliqueProjectionMatrixList::ObliqueProjectionMatrixList(double widthInScene, double heightInScene, int widthByPixel, int heightByPixel, double widthBymm, double heightBymm, double thicknessBymm, double refractionIndex)
{
	wInScene = widthInScene;	//Decided by the WH ratio and heightInScene.
	hInScene = heightInScene;	//Usually it would be 2. 
	wByPixel = widthByPixel;	//It is for the subimages, not the entire display zone.
	hByPixel = heightByPixel;	//It is for the subimages, not the entire display zone.
	wBymm = widthBymm;			//It is for the subimages, not the entire display zone.
	hBymm = heightBymm;			//It is for the subimages, not the entire display zone.
	tBymm = thicknessBymm;		//It is for the subimages, not the entire display zone.
	refractionI = refractionIndex;

	matrixList.resize(wByPixel);
	for (int i = 0; i < wByPixel; i++)
	{
		matrixList[i].resize(hByPixel);
		for (int j = 0; j < hByPixel; j++)
		{
			matrixList[i][j] = new irr::core::matrix4();
			irr::core::matrix4* projectionMatrix = new irr::core::matrix4();
			projectionMatrix->buildProjectionMatrixOrthoLH(wInScene, hInScene, -10000, 10000);
			irr::core::matrix4* obliqueMatrix = new irr::core::matrix4();

			double x = wBymm / 2 + (-0.5 - (double)i) * wBymm / wByPixel;
			double y = ((double)j + 0.5) * hBymm / hByPixel - hBymm / 2;
			double h = sqrt(((pow(x,2) + pow(y,2)) * (1 - refractionI) * (1 + refractionI) + pow(tBymm,2))) / refractionI; //The interesting thing is, there will still be some outputs even if the input is a negative value... Not so sure if it is a good thing. but for test it is enough.


			irr::f32 valueOfMatrixElement[16] = {
				1,0,0,0,
				0,1,0,0,
				x / h,
				y / h,
				1,0,
				0,0,0,1 };
			obliqueMatrix->setM(valueOfMatrixElement);
			matrixList[i][j]->setbyproduct(*projectionMatrix, *obliqueMatrix); //Something need to be aware of is that irr::core::matrix4::setbyproduct(A,B) will return the result of BA, rather than AB.
		}
	}
}

ObliqueProjectionMatrixList::~ObliqueProjectionMatrixList()
{
}

irr::core::matrix4 * ObliqueProjectionMatrixList::getProjectionByPixel(int x, int y)
{
	return matrixList[x][y];
}