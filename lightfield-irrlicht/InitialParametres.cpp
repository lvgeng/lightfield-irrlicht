#include "InitialParametres.h"

InitialParametres::InitialParametres()
{
	widthOfDisplayzoneByPixel = 1200;
	heightOfDisplayzoneByPixel = 640;


	heightOfProjectionPanelInScene = 2;
	widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfDisplayzoneByPixel / heightOfDisplayzoneByPixel;

	isFullscreen = false;

	widthOfSubimageByPixel = 20;
	heightOfSubimageByPixel = 20;

	widthOfSubimageBymm = 20;
	heightOfSubimageBymm = 20;
	thicknessOfTransparentMaterialBetweenDevices = 20;

	refractionIndexOfTransparentMaterial = 1.49; //The data comes from the data sheet is 1.49. Do not change it if unnecessary.

	xSubimageCountMax = widthOfDisplayzoneByPixel / widthOfSubimageByPixel;
	ySubimageCountMax = heightOfDisplayzoneByPixel / heightOfSubimageByPixel;

	isCubeSpinning = true;
	//isSimulating = false;
	isSimulating = true;
}

InitialParametres::~InitialParametres()
{
}
