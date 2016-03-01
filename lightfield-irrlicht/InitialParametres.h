#pragma once

#include <vector>
#include <irrlicht.h>
#include "pugixml.hpp"

class InitialParametres
{
public:
	//display setting
	int widthOfDisplayzoneByPixel;
	int heightOfDisplayzoneByPixel;
	bool isFullscreen;
	int widthOfSubimageByPixel;
	int heightOfSubimageByPixel;
	//real world setting
	double widthOfSubimageBymm;
	double heightOfSubimageBymm;
	double thicknessOfTransparentMaterialBetweenDevices;
	double refractionIndexOfTransparentMaterial;

	//function setting
	bool isCubeEnabled;
	bool isFighterEnabled;
	bool isTestSubjectSpinning;
	bool isSimulating;

	//Calculated.
	double widthOfProjectionPanelInScene;
	double heightOfProjectionPanelInScene;
	int xSubimageCountMax;
	int ySubimageCountMax;


	void defaultValuesInitializing();
	~InitialParametres();
	InitialParametres();
	InitialParametres(char* xmlConfigFilePath);
};
