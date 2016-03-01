#include "InitialParametres.h"

void InitialParametres::defaultValuesInitializing()
{
	widthOfDisplayzoneByPixel = 800;
	heightOfDisplayzoneByPixel = 600;
	isFullscreen = false;
	widthOfSubimageByPixel = 20;
	heightOfSubimageByPixel = 20;

	widthOfSubimageBymm = 5.6;
	heightOfSubimageBymm = 5.6;
	thicknessOfTransparentMaterialBetweenDevices = 3;
	refractionIndexOfTransparentMaterial = 1.49;
	//The data comes from the data sheet is 1.49. Do not change it if unnecessary.
	isCubeEnabled = true;
	isFighterEnabled = false;
	isTestSubjectSpinning = false;
	isSimulating = false;

	heightOfProjectionPanelInScene = 2;
	widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfDisplayzoneByPixel / heightOfDisplayzoneByPixel;
	xSubimageCountMax = widthOfDisplayzoneByPixel / widthOfSubimageByPixel;
	ySubimageCountMax = heightOfDisplayzoneByPixel / heightOfSubimageByPixel;
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
		nodeDisplaySetting.append_child("widthOfDisplayzoneByPixel").append_attribute("value") = widthOfDisplayzoneByPixel;
		nodeDisplaySetting.append_child("heightOfDisplayzoneByPixel").append_attribute("value") = heightOfDisplayzoneByPixel;
		nodeDisplaySetting.append_child("isFullscreen").append_attribute("value") = isFullscreen;
		nodeDisplaySetting.append_child("widthOfSubimageByPixel").append_attribute("value") = widthOfSubimageByPixel;
		nodeDisplaySetting.append_child("heightOfSubimageByPixel").append_attribute("value") = heightOfSubimageByPixel;

		pugi::xml_node nodeRealworldSetting = nodeSettings.append_child("realworldSetting");
		nodeRealworldSetting.append_child("widthOfSubimageBymm").append_attribute("value") = widthOfSubimageBymm;
		nodeRealworldSetting.append_child("heightOfSubimageBymm").append_attribute("value") = heightOfSubimageBymm;
		nodeRealworldSetting.append_child("thicknessOfTransparentMaterialBetweenDevices").append_attribute("value") = thicknessOfTransparentMaterialBetweenDevices;
		nodeRealworldSetting.append_child("refractionIndexOfTransparentMaterial").append_attribute("value") = refractionIndexOfTransparentMaterial;

		pugi::xml_node nodeFunctionSetting = nodeSettings.append_child("functionSetting");
		nodeFunctionSetting.append_child("isCubeEnabled").append_attribute("value") = isCubeEnabled;
		nodeFunctionSetting.append_child("isFighterEnabled").append_attribute("value") = isFighterEnabled;
		nodeFunctionSetting.append_child("isTestSubjectSpinning").append_attribute("value") = isTestSubjectSpinning;
		nodeFunctionSetting.append_child("isSimulating").append_attribute("value") = isSimulating;

		doc.save_file(xmlConfigFilePath);
	}
	else
	{
		widthOfDisplayzoneByPixel = doc.child("Settings").child("displaySetting").child("widthOfDisplayzoneByPixel").attribute("value").as_int();
		heightOfDisplayzoneByPixel = doc.child("Settings").child("displaySetting").child("heightOfDisplayzoneByPixel").attribute("value").as_int();
		isFullscreen = doc.child("Settings").child("displaySetting").child("isFullscreen").attribute("value").as_bool();
		widthOfSubimageByPixel = doc.child("Settings").child("displaySetting").child("widthOfSubimageByPixel").attribute("value").as_int();
		heightOfSubimageByPixel = doc.child("Settings").child("displaySetting").child("heightOfSubimageByPixel").attribute("value").as_int();

		widthOfSubimageBymm = doc.child("Settings").child("realworldSetting").child("widthOfSubimageBymm").attribute("value").as_double();
		heightOfSubimageBymm = doc.child("Settings").child("realworldSetting").child("heightOfSubimageBymm").attribute("value").as_double();
		thicknessOfTransparentMaterialBetweenDevices = doc.child("Settings").child("realworldSetting").child("thicknessOfTransparentMaterialBetweenDevices").attribute("value").as_double();
		refractionIndexOfTransparentMaterial = doc.child("Settings").child("realworldSetting").child("refractionIndexOfTransparentMaterial").attribute("value").as_double();

		isCubeEnabled = doc.child("Settings").child("functionSetting").child("isCubeEnabled").attribute("value").as_bool();
		isFighterEnabled = doc.child("Settings").child("functionSetting").child("isFighterEnabled").attribute("value").as_bool();
		isTestSubjectSpinning = doc.child("Settings").child("functionSetting").child("isTestSubjectSpinning").attribute("value").as_bool();
		isSimulating = doc.child("Settings").child("functionSetting").child("isSimulating").attribute("value").as_bool();

		heightOfProjectionPanelInScene = 2;
		widthOfProjectionPanelInScene = heightOfProjectionPanelInScene * widthOfDisplayzoneByPixel / heightOfDisplayzoneByPixel;
		xSubimageCountMax = widthOfDisplayzoneByPixel / widthOfSubimageByPixel;
		ySubimageCountMax = heightOfDisplayzoneByPixel / heightOfSubimageByPixel;
	}
}
