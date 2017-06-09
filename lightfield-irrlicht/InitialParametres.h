#pragma once

#include <vector>
#include <irrlicht.h>
#include <iostream>
#include <irrlicht.h>
#include "pugixml.hpp"

#include <chrono>

using namespace std;
using namespace chrono;

//class DiaplayedObject
//{
//public:
//	bool isEnabled;
//	std::string filepath;
//
//	float scale;
//
//	float rotationX;
//	float rotationY;
//	float rotationZ;
//
//	float positionX;
//	float positionY;
//	float positionZ;
//
//};

class InitialParametres
{
public:
	//display setting
	int widthOfRenderzoneByPixel;
	int heightOfRenderzoneByPixel;
	bool isFullscreen;
	int widthOfSubimageByPixel;
	int heightOfSubimageByPixel;

	int xOffsetByPixel;
	int yOffsetByPixel;
	//real world setting
	double widthOfSubimageBymm;
	double heightOfSubimageBymm;

	double widthOfRenderzoneBymm;
	double heightOfRenderzoneBymm;
	
	double thicknessOfTransparentMaterialBetweenDevices;
	double refractionIndexOfTransparentMaterial;

	//function setting
	int backgroundColorR;
	int backgroundColorG;
	int backgroundColorB;

	bool isMeshOneEnabled;
	std::string meshOneModelPath;
	float meshOneScale;
	float meshOneRotationX;
	float meshOneRotationY;
	float meshOneRotationZ;

	float meshOnePositionX;
	float meshOnePositionY;
	float meshOnePositionZ;

	bool isMeshTwoEnabled;
	std::string meshTwoModelPath;
	float meshTwoScale;
	float meshTwoRotationX;
	float meshTwoRotationY;
	float meshTwoRotationZ;
	float meshTwoPositionX;
	float meshTwoPositionY;
	float meshTwoPositionZ;

	bool isMeshThreeEnabled;
	std::string meshThreeModelPath;
	float meshThreeScale;
	float meshThreeRotationX;
	float meshThreeRotationY;
	float meshThreeRotationZ;
	float meshThreePositionX;
	float meshThreePositionY;
	float meshThreePositionZ;

	bool isTestSubjectSpinning;
	bool isAimmingAssistantEnabled;
	//bool isSimulating;
	bool isSingleFrameRenderingAndQuitMode;

	bool isLightField;
	float virtualCameraPosX;
	float virtualCameraPosY;
	float virtualCameraPosZ;
	float virtualCameraFOV;

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
