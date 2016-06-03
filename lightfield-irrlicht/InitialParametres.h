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
	//real world setting
	double widthOfSubimageBymm;
	double heightOfSubimageBymm;

	double widthOfRenderzoneBymm;
	double heightOfRenderzoneBymm;
	
	double thicknessOfTransparentMaterialBetweenDevices;
	double refractionIndexOfTransparentMaterial;

	//function setting
	bool isCubeEnabled;
	std::string cubeModelPath;
	float cubeScale;
	float cubeRotationX;
	float cubeRotationY;
	float cubeRotationZ;

	float cubePositionX;
	float cubePositionY;
	float cubePositionZ;

	bool isBunnyEnabled;
	std::string bunnyModelPath;
	float bunnyScale;
	float bunnyRotationX;
	float bunnyRotationY;
	float bunnyRotationZ;
	float bunnyPositionX;
	float bunnyPositionY;
	float bunnyPositionZ;

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
