#include <irrlicht.h>
//#include <SIrrCreationParameters.h>

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string>

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

void savetex(ITexture *texture, std::string filename, IVideoDriver* videoDriver) {

	// void* imageData = texture->lock(true);
	video::IImage* image = videoDriver->createImageFromData (
		texture->getColorFormat(),
		texture->getSize(),
		texture->lock( irr::video::E_TEXTURE_LOCK_MODE::ETLM_READ_WRITE),
		true  //copy mem
	);

	videoDriver->writeImageToFile(image, path(filename.c_str()));
	texture->unlock();
}


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
		if (argc == 5 && std::string(argv[1])=="t")
		{
			isTesting = true;
			widthOfDisplayZone = atoi(argv[2]);
			widthOfSubimage = atoi(argv[3]);
			heightOfSubimage = widthOfSubimage;
			widthOfHole = atoi(argv[4]);
			heightOfHole = widthOfHole;
		}
		else if (argc == 4 && atoi(argv[1]) != 0)
		{
			isTesting = false;
			widthOfDisplayZone = atoi(argv[1]);
			widthOfSubimage = atoi(argv[2]);
			heightOfSubimage = widthOfSubimage;
			widthOfHole = atoi(argv[3]);
			heightOfHole = widthOfHole;
		}
		else
		{
			throw 0;
		}
	}
	catch(int error)
	{
		cout<<"Usage:\n"<<"'./pattern-irrlicht t HEIGHT WIDTHOFHOLE' for testing images\n"<<"'./pattern-irrlicht HEIGHT WIDTHOFHOLE' for images for using\n";
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

	video::IRenderTarget* simulatorRenderTarget = 0;
	video::ITexture* renderTargetTex = 0;
	scene::ICameraSceneNode* fixedCam = 0;
	renderTargetTex = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(widthOfDisplayZone,heightOfDisplayZone), "RTT1", video::ECF_A8R8G8B8);
	video::ITexture* renderTargetDepth = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(widthOfDisplayZone,heightOfDisplayZone), "DepthStencil", video::ECF_D24S8);
	simulatorRenderTarget = videoDriver->addRenderTarget();
	simulatorRenderTarget->setTexture(renderTargetTex, renderTargetDepth);
	videoDriver->setRenderTargetEx(simulatorRenderTarget, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(0));


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

	for (int xSubimageCount = 0; xSubimageCount < widthOfDisplayZone / widthOfSubimage; xSubimageCount++)
	{
		for (int ySubimageCount = 0; ySubimageCount < heightOfDisplayZone / heightOfSubimage; ySubimageCount++)
		{
			videoDriver->draw2DRectangle(
				dotColor,
				core::rect<s32>(
					(xSubimageCount + 0.5) * widthOfSubimage - widthOfHole / 2,
					(ySubimageCount + 0.5) * heightOfSubimage - heightOfHole / 2,
					(xSubimageCount + 0.5) * widthOfSubimage + widthOfHole / 2 ,
					(ySubimageCount + 0.5) * heightOfSubimage + heightOfHole / 2
					)
				);

			if (isTesting && xSubimageCount % 5 == 0 && ySubimageCount % 5 == 0)
			{
				IGUIStaticText* coordinatesInformationTextBox = guiEnvironment->addStaticText(
					L"this is text",
				rect<s32>(xSubimageCount * widthOfSubimage, ySubimageCount * heightOfSubimage, (xSubimageCount + 3) * widthOfSubimage, (ySubimageCount + 3) * heightOfSubimage), true);
				core::stringw displayStr = L"(";
				displayStr += xSubimageCount * widthOfSubimage;
				displayStr += ", ";
				displayStr += ySubimageCount * heightOfSubimage;
				displayStr += ")";
				coordinatesInformationTextBox->setText(displayStr.c_str());
			}
		}
	}

	guiEnvironment->drawAll();	

	videoDriver->setRenderTargetEx(0, 0, SColor(0));
	videoDriver->draw2DImage(renderTargetTex,	core::position2d< s32 >(100,100));
	videoDriver->endScene();

	if(isTesting)
	{
		filename = "Img-testing-" + to_string(widthOfDisplayZone) + "-" + to_string(heightOfDisplayZone) + ".png";
	}
	else
	{
		filename = "Img-" + to_string(widthOfDisplayZone) + "-" + to_string(heightOfDisplayZone) + ".png";
	}
	savetex(renderTargetTex,filename,videoDriver);
  while(device->run());
}
