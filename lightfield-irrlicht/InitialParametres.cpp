#include "InitialParametres.h"

InitialParametres::InitialParametres()
{
	widthOfDisplayzoneByPixel = 800;
	heightOfDisplayzoneByPixel = 600;


	heightOfProjectionPanelInScene = 2;
	widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfDisplayzoneByPixel / heightOfDisplayzoneByPixel;

	isFullscreen = false;

	widthOfSubimageByPixel = 20;
	heightOfSubimageByPixel = 20;

	widthOfSubimageBymm = 5.6;
	heightOfSubimageBymm = 5.6;
	thicknessOfTransparentMaterialBetweenDevices = 3;

	refractionIndexOfTransparentMaterial = 1.49; //The data comes from the data sheet is 1.49. Do not change it if unnecessary.

	xSubimageCountMax = widthOfDisplayzoneByPixel / widthOfSubimageByPixel;
	ySubimageCountMax = heightOfDisplayzoneByPixel / heightOfSubimageByPixel;

	isCubeSpinning = false;
	//isCubeSpinning = true;
	isSimulating = false;
	//isSimulating = true;
}

InitialParametres::~InitialParametres()
{
}
