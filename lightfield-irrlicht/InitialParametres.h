#pragma once

#include <vector>
#include <irrlicht.h>
#include "pugixml.hpp"

class InitialParametres
{
public:
	//display setting
	int widthOfRenderzoneByPixel;
	int heightOfRenderzoneByPixel;
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

	float cubeScale;

	float cubeRotationX;
	float cubeRotationY;
	float cubeRotationZ;

	float cubePositionX;
	float cubePositionY;
	float cubePositionZ;

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
