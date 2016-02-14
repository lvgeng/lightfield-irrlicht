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
	InitialParametres(
		int	widthOfDisplayzoneByPixelInput,
		int	heightOfDisplayzoneByPixelInput,
		double widthOfProjectionPanelInSceneInput,
		double heightOfProjectionPanelInSceneInput,
		bool isFullscreenInput,
		int	widthOfSubimageByPixelInput,
		int	heightOfSubimageByPixelInput,
		double widthOfSubimageBymmInput,
		double heightOfSubimageBymmInput,
		double thicknessOfTransparentMaterialBetweenDevicesInput,
		double refractionIndexOfTransparentMaterialInput,
		int	xSubimageCountMaxInput,
		int	ySubimageCountMaxInput,
		bool isTestSubjectSpinningInput,
		bool isSimulatingInput
		);
};
