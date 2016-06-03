#include "InitialParametres.h"
#include <iostream>

void InitialParametres::defaultValuesInitializing()
{
	widthOfRenderzoneByPixel = 800;
	heightOfRenderzoneByPixel = 600;
	isFullscreen = false;
	widthOfSubimageByPixel = 20;
	heightOfSubimageByPixel = 20;

	widthOfSubimageBymm = 5.6;
	heightOfSubimageBymm = 5.6;
	widthOfRenderzoneBymm = 224;
	heightOfRenderzoneBymm = 168;

	thicknessOfTransparentMaterialBetweenDevices = 3.15;
	refractionIndexOfTransparentMaterial = 1.491756;
	//The data comes from the data sheet is 1.491756. Do not change it if unnecessary.
	isCubeEnabled = true;
	cubeModelPath = "../media/cube.dae";
	cubeScale = 0.4;
	cubeRotationX = 0;
	cubeRotationY = 30;
	cubeRotationZ = 0;
	cubePositionX = 0;
	cubePositionY = 0;
	cubePositionZ = 0.3;

	isBunnyEnabled = false;
	bunnyModelPath = "../media/bun_zipper-blender.obj";
	bunnyScale = 1;
	bunnyRotationX = 0;
	bunnyRotationY = 0;
	bunnyRotationZ = 0;
	bunnyPositionX = 0;
	bunnyPositionY = -0.2;
	bunnyPositionZ = 0.3;

	isTestSubjectSpinning = false;
	isSimulating = false;
	isSingleFrameRenderingAndQuitMode = false;

	heightOfProjectionPanelInScene = 2;
	widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfRenderzoneByPixel / heightOfRenderzoneByPixel;
	xSubimageCountMax = widthOfRenderzoneByPixel / widthOfSubimageByPixel;
	ySubimageCountMax = heightOfRenderzoneByPixel / heightOfSubimageByPixel;
}

InitialParametres::~InitialParametres()
{
}

InitialParametres::InitialParametres()
{
	defaultValuesInitializing();
}

InitialParametres::InitialParametres(char* xmlConfigFilePath)
{
	pugi::xml_document doc;
	pugi::xml_parse_result resultConfigfile = doc.load_file(xmlConfigFilePath);
	if (!resultConfigfile)
	{
		defaultValuesInitializing();
    //pugi::xml_document doc;
    // add node with some name
    pugi::xml_node nodeSettings = doc.append_child("Settings");
		pugi::xml_node nodeDisplaySetting = nodeSettings.append_child("displaySetting");
			nodeDisplaySetting.append_child("widthOfRenderzoneByPixel").append_attribute("value") = widthOfRenderzoneByPixel;
			nodeDisplaySetting.append_child("heightOfRenderzoneByPixel").append_attribute("value") = heightOfRenderzoneByPixel;
			nodeDisplaySetting.append_child("isFullscreen").append_attribute("value") = isFullscreen;
			nodeDisplaySetting.append_child("widthOfSubimageByPixel").append_attribute("value") = widthOfSubimageByPixel;
			nodeDisplaySetting.append_child("heightOfSubimageByPixel").append_attribute("value") = heightOfSubimageByPixel;

		pugi::xml_node nodeRealworldSetting = nodeSettings.append_child("realworldSetting");
			nodeRealworldSetting.append_child("widthOfSubimageBymm").append_attribute("value") = widthOfSubimageBymm;
			nodeRealworldSetting.append_child("heightOfSubimageBymm").append_attribute("value") = heightOfSubimageBymm;

			nodeRealworldSetting.append_child("widthOfRenderzoneBymm").append_attribute("value") = widthOfRenderzoneBymm;
			nodeRealworldSetting.append_child("heightOfRenderzoneBymm").append_attribute("value") = heightOfRenderzoneBymm;

			nodeRealworldSetting.append_child("thicknessOfTransparentMaterialBetweenDevices").append_attribute("value") = thicknessOfTransparentMaterialBetweenDevices;
			nodeRealworldSetting.append_child("refractionIndexOfTransparentMaterial").append_attribute("value") = refractionIndexOfTransparentMaterial;
			
		pugi::xml_node nodeFunctionSetting = nodeSettings.append_child("functionSetting");
			pugi::xml_node nodeIsCubeEnabled = nodeFunctionSetting.append_child("isCubeEnabled");
				nodeIsCubeEnabled.append_attribute("value") = isCubeEnabled;
					nodeIsCubeEnabled.append_child("cubeModelPath").append_attribute("value") = cubeModelPath.c_str();
					nodeIsCubeEnabled.append_child("cubeScale").append_attribute("value") = cubeScale;
					nodeIsCubeEnabled.append_child("cubeRotationX").append_attribute("value") = cubeRotationX;
					nodeIsCubeEnabled.append_child("cubeRotationY").append_attribute("value") = cubeRotationY;
					nodeIsCubeEnabled.append_child("cubeRotationZ").append_attribute("value") = cubeRotationZ;

					nodeIsCubeEnabled.append_child("cubePositionX").append_attribute("value") = cubePositionX;
					nodeIsCubeEnabled.append_child("cubePositionY").append_attribute("value") = cubePositionY;
					nodeIsCubeEnabled.append_child("cubePositionZ").append_attribute("value") = cubePositionZ;

			pugi::xml_node nodeIsBunnyEnabled = nodeFunctionSetting.append_child("isBunnyEnabled");
				nodeIsBunnyEnabled.append_attribute("value") = isBunnyEnabled;
					nodeIsBunnyEnabled.append_child("bunnyModelPath").append_attribute("value") = bunnyModelPath.c_str();
					nodeIsBunnyEnabled.append_child("bunnyScale").append_attribute("value") = bunnyScale;
					nodeIsBunnyEnabled.append_child("bunnyRotationX").append_attribute("value") = bunnyRotationX;
					nodeIsBunnyEnabled.append_child("bunnyRotationY").append_attribute("value") = bunnyRotationY;
					nodeIsBunnyEnabled.append_child("bunnyRotationZ").append_attribute("value") = bunnyRotationZ;

					nodeIsBunnyEnabled.append_child("bunnyPositionX").append_attribute("value") = bunnyPositionX;
					nodeIsBunnyEnabled.append_child("bunnyPositionY").append_attribute("value") = bunnyPositionY;
					nodeIsBunnyEnabled.append_child("bunnyPositionZ").append_attribute("value") = bunnyPositionZ;
			//nodeFunctionSetting.append_child("isFighterEnabled").append_attribute("value") = isFighterEnabled;
			nodeFunctionSetting.append_child("isTestSubjectSpinning").append_attribute("value") = isTestSubjectSpinning;
			nodeFunctionSetting.append_child("isSimulating").append_attribute("value") = isSimulating;
			nodeFunctionSetting.append_child("isSingleFrameRenderingAndQuitMode").append_attribute("value") = isSingleFrameRenderingAndQuitMode;

		doc.save_file(xmlConfigFilePath);
	}
	else
	{
		widthOfRenderzoneByPixel = doc.child("Settings").child("displaySetting").child("widthOfRenderzoneByPixel").attribute("value").as_int();
		heightOfRenderzoneByPixel = doc.child("Settings").child("displaySetting").child("heightOfRenderzoneByPixel").attribute("value").as_int();
		isFullscreen = doc.child("Settings").child("displaySetting").child("isFullscreen").attribute("value").as_bool();
		widthOfSubimageByPixel = doc.child("Settings").child("displaySetting").child("widthOfSubimageByPixel").attribute("value").as_int();
		heightOfSubimageByPixel = doc.child("Settings").child("displaySetting").child("heightOfSubimageByPixel").attribute("value").as_int();

		widthOfSubimageBymm = doc.child("Settings").child("realworldSetting").child("widthOfSubimageBymm").attribute("value").as_double();
		heightOfSubimageBymm = doc.child("Settings").child("realworldSetting").child("heightOfSubimageBymm").attribute("value").as_double();

		// std::cout << " Loading XML widthOfSubimageBymm = " << widthOfSubimageBymm << "\n\n";

		widthOfRenderzoneBymm = doc.child("Settings").child("realworldSetting").child("widthOfRenderzoneBymm").attribute("value").as_double();
		heightOfRenderzoneBymm = doc.child("Settings").child("realworldSetting").child("heightOfRenderzoneBymm").attribute("value").as_double();

		// std::cout << " Loading XML widthOfRenderzoneBymm = " << widthOfRenderzoneBymm << "\n\n";


		
		thicknessOfTransparentMaterialBetweenDevices = doc.child("Settings").child("realworldSetting").child("thicknessOfTransparentMaterialBetweenDevices").attribute("value").as_double();
		refractionIndexOfTransparentMaterial = doc.child("Settings").child("realworldSetting").child("refractionIndexOfTransparentMaterial").attribute("value").as_double();

		isCubeEnabled = doc.child("Settings").child("functionSetting").child("isCubeEnabled").attribute("value").as_bool();
		cubeModelPath = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubeModelPath").attribute("value").as_string();
		cubeScale = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubeScale").attribute("value").as_float();		
		cubeRotationX = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubeRotationX").attribute("value").as_float();
		cubeRotationY = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubeRotationY").attribute("value").as_float();
		cubeRotationZ = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubeRotationZ").attribute("value").as_float();
		cubePositionX = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubePositionX").attribute("value").as_float();
		cubePositionY = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubePositionY").attribute("value").as_float();
		cubePositionZ = doc.child("Settings").child("functionSetting").child("isCubeEnabled").child("cubePositionZ").attribute("value").as_float();

		isBunnyEnabled = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").attribute("value").as_bool();
		bunnyModelPath = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyModelPath").attribute("value").as_string();
		bunnyScale = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyScale").attribute("value").as_float();
		bunnyRotationX = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyRotationX").attribute("value").as_float();
		bunnyRotationY = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyRotationY").attribute("value").as_float();
		bunnyRotationZ = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyRotationZ").attribute("value").as_float();
		bunnyPositionX = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyPositionX").attribute("value").as_float();
		bunnyPositionY = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyPositionY").attribute("value").as_float();
		bunnyPositionZ = doc.child("Settings").child("functionSetting").child("isBunnyEnabled").child("bunnyPositionZ").attribute("value").as_float();

		isTestSubjectSpinning = doc.child("Settings").child("functionSetting").child("isTestSubjectSpinning").attribute("value").as_bool();
		isSimulating = doc.child("Settings").child("functionSetting").child("isSimulating").attribute("value").as_bool();
		isSingleFrameRenderingAndQuitMode = doc.child("Settings").child("functionSetting").child("isSingleFrameRenderingAndQuitMode").attribute("value").as_bool();

		heightOfProjectionPanelInScene = 2;
		widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfRenderzoneByPixel / heightOfRenderzoneByPixel;
		xSubimageCountMax = widthOfRenderzoneByPixel / widthOfSubimageByPixel;
		ySubimageCountMax = heightOfRenderzoneByPixel / heightOfSubimageByPixel;
	}
}
