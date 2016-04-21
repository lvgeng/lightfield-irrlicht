#pragma once

#include <vector>
#include <irrlicht.h>
#include <iostream>
#include <irrlicht.h>
#include "pugixml.hpp"

class DiaplayedObject
{
public:
	bool isEnabled;
	// io::path * filePath;
	char filepath[];

	float scale;

	float rotationX;
	float rotationY;
	float rotationZ;

	float positionX;
	float positionY;
	float positionZ;

};

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

	double widthOfRenderzoneBymm;
	double heightOfRenderzoneBymm;
	
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
	bool isSingleFrameRenderingAndQuitMode;

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
