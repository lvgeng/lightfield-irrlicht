#pragma once

#include <vector>
#include <irrlicht.h>

class InitialParametres
{
public:
	int widthOfDisplayzoneByPixel;
	int heightOfDisplayzoneByPixel;

	double widthOfProjectionPanelInScene;
	double heightOfProjectionPanelInScene;

	bool isFullscreen;

	int widthOfSubimageByPixel;
	int heightOfSubimageByPixel;

	double widthOfSubimageBymm;
	double heightOfSubimageBymm;
	double thicknessOfTransparentMaterialBetweenDevices;
	
	double refractionIndexOfTransparentMaterial;

	int xSubimageCountMax;
	int ySubimageCountMax;

	bool isCubeSpinning;
	bool isSimulating;

	InitialParametres();
	~InitialParametres();
};