#include <irrlicht.h>
#include <SIrrCreationParameters.h>

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace chrono;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//This is the main method. We can now use main() on every platform.

int main(int argc, char* argv[])
{
	int widthOfDisplayZone = 800;
	int heightOfDisplayZone = 600;
	int widthOfSubimage = 20;
	int heightOfSubimage = 20;
	int widthOfHole = 2;
	int heightOfHole = 2;
	video::SColor backgroundColor;
	video::SColor dotColor;
	std::string filename;

	bool isTesting = true;

	try
	{
		if (argc == 3 && std::string(argv[1])=="t")
		{
			isTesting = true;
			widthOfDisplayZone = atoi(argv[2]);
		}
		else if (argc == 2 && atoi(argv[1]) != 0)
		{
			isTesting = false;
			widthOfDisplayZone = atoi(argv[1]);
		}
		else
		{
			throw 0;
		}
	}
	catch(int error)
	{
		cout<<"Usage:\n"<<"'./pattern-irrlicht t HEIGHT' for testing images\n"<<"'./pattern-irrlicht HEIGHT' for images for using\n";
		return 0;
	}


	

	// Load the width and height.
	heightOfDisplayZone = widthOfDisplayZone * 210 / 297;

	if(isTesting)
	{
		backgroundColor = SColor(255,255,255,255);
		dotColor = SColor(255,0,0,0); 		
	}
	else
	{
		backgroundColor = SColor(255,0,0,0);
		dotColor = SColor(255,255,255,255);
	}


	// SIrrlichtCreationParameters creationParameter;
	// creationParameter.DriverType = video::EDT_OPENGL;
	// creationParameter.WindowSize = dimension2d<u32>(widthOfDisplayZone, heightOfDisplayZone);
	// creationParameter.Bits = 32;
	// creationParameter.Fullscreen = false;
	// creationParameter.Stencilbuffer = true;
	// creationParameter.Vsync = true;

	// IrrlichtDevice *device = createDeviceEx(creationParameter);
	// if (!device)
	// {
	// 	return 1;
	// }

	// widthOfDisplayZone = 1920;
	// heightOfDisplayZone = 1080;

	
	IrrlichtDevice *device =
		createDevice(
			video::EDT_OPENGL,				//- deviceType: Type of the device. This can currently be the Null-device,one of the two software renderers, D3D8, D3D9, or OpenGL.In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			//video::EDT_DIRECT3D9,
			dimension2d<u32>(widthOfDisplayZone, heightOfDisplayZone),
											//- windowSize: Size of the Window or screen in FullScreenMode to be created.
			16,								//- bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			false,//- fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			true,							//- stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			true,							//- vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			0								//- eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
			);


	device->setWindowCaption(L"Light field display");

	IVideoDriver* videoDriver = device->getVideoDriver();
	ISceneManager* sceneManager = device->getSceneManager();
	IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

	if(isTesting)
	{
		IGUIStaticText* informationTextBox = guiEnvironment->addStaticText(L"this is text", rect<s32>(15,15,260,30), true);
		core::stringw displayStr = L"Width = ";
		displayStr += widthOfDisplayZone;
		displayStr += " Height = ";
		displayStr += heightOfDisplayZone;
		informationTextBox->setText(displayStr.c_str());		
	}

	videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, backgroundColor);

	for (int xSubimageCount = 0; xSubimageCount < widthOfDisplayZone/widthOfSubimage; xSubimageCount++)
	{
		for (int ySubimageCount = 0; ySubimageCount < heightOfDisplayZone/heightOfSubimage; ySubimageCount++)
		{
			videoDriver->draw2DRectangle(
				dotColor,
				core::rect<s32>(
					(xSubimageCount + 0.5) * widthOfSubimage + widthOfHole/2,
					(ySubimageCount + 0.5) * heightOfSubimage + heightOfHole/2,
					(xSubimageCount + 0.5) * widthOfSubimage + widthOfHole/2*3,
					(ySubimageCount + 0.5) * heightOfSubimage + heightOfHole/2*3
					)
				);
		}
	}

	guiEnvironment->drawAll();
	videoDriver->endScene();

	// char filenameSharedBegining[] = "Img";
	// char filenameSharedEnding[] = ".png";
	// char buffer [33];

	// char * filename = new char[strlen(filenameSharedBegining)+strlen(filenameSharedEnding)+strlen(itoa(widthOfDisplayZone, buffer, 10))+strlen(itoa(heightOfDisplayZone, buffer, 10)) + 3];
	// strcpy(filename, filenameSharedBegining);
	// strcat(filename, "-");
	// strcpy(filename, itoa(widthOfDisplayZone, buffer, 10));
	// strcat(filename, "-");
	// strcpy(filename, itoa(heightOfDisplayZone, buffer, 10));
	// strcat(filename, filenameSharedEnding);

	// filename = "Img-" + to_string(widthOfDisplayZone) + "-" + to_string(heightOfDisplayZone) + ".png";

	if(isTesting)
	{
		filename = "Img-testing-" + to_string(widthOfDisplayZone) + "-" + to_string(heightOfDisplayZone) + ".png";
	}
	else
	{
		filename = "Img-" + to_string(widthOfDisplayZone) + "-" + to_string(heightOfDisplayZone) + ".png";
	}


	videoDriver->writeImageToFile(videoDriver->createScreenShot(), path(filename.c_str()));
	while(device->run());
}
