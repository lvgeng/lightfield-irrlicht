#include <irrlicht.h>
#include <GL/freeglut.h>
#include "ObliqueMatrixList.h"
#include "InitialParametres.h"
#include "EventReceiverForKeyboard.h"
#include "PlaneSimulator.h"


#include <iostream>
#include <chrono>

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
	video::IImage* image = videoDriver->createImageFromData(
		texture->getColorFormat(),
		texture->getSize(),
		texture->lock(irr::video::E_TEXTURE_LOCK_MODE::ETLM_READ_WRITE),
		true  //copy mem
		);
	videoDriver->writeImageToFile(image, path(filename.c_str()));
	texture->unlock();
}

int main()
{

	//The data use for initializing. It is static since there is no need to update after initializing.
	static InitialParametres *initialParametres = new InitialParametres("setting.xml");
	//The oblique projection matrix list. Only related to the projection configuration.
	static ObliqueMatrixList* obliqueMatrixList = new ObliqueMatrixList(
		initialParametres->widthOfProjectionPanelInScene,					//Width in scene. Relative.
		initialParametres->heightOfProjectionPanelInScene,					//Height in scene. Relative.
		initialParametres->widthOfSubimageByPixel,							//Width of the subimage. (pixel)
		initialParametres->heightOfSubimageByPixel,							//Height of the subimage. (pixel)
		initialParametres->widthOfSubimageBymm,								//Width of the subimage. (mm)
		initialParametres->heightOfSubimageBymm,							//Height of the subimage. (mm)
		initialParametres->widthOfRenderzoneBymm,
		initialParametres->heightOfRenderzoneBymm,
		initialParametres->thicknessOfTransparentMaterialBetweenDevices,	//Thickness of the transparent material between the light barriers and the screen. It will affect the result because of the refraction.
		initialParametres->refractionIndexOfTransparentMaterial				//Rafraction index of the transparent material.
		);

	IrrlichtDevice *device =
		createDevice(
			video::EDT_OPENGL,				//- deviceType: Type of the device. This can currently be the Null-device,one of the two software renderers, D3D8, D3D9, or OpenGL.In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			//video::EDT_DIRECT3D9,
			dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel),
			//- windowSize: Size of the Window or screen in FullScreenMode to be created.
			16,								//- bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			initialParametres->isFullscreen,//- fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			true,							//- stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			true,							//- vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			0								//- eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
			);


	device->setWindowCaption(L"Light field display");

	IVideoDriver* videoDriver = device->getVideoDriver();
	ISceneManager* sceneManager = device->getSceneManager();
	IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();


	//Preparing for the renderTarget.
	video::IRenderTarget* renderTargetAllSubimages = 0;
	video::ITexture* renderTargetTex = 0;
	scene::ICameraSceneNode* fixedCam = 0;
	renderTargetTex = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel), "RTT1", video::ECF_A8R8G8B8);
	video::ITexture* renderTargetDepth = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(initialParametres->widthOfRenderzoneByPixel, initialParametres->heightOfRenderzoneByPixel), "DepthStencil", video::ECF_D24S8);
	renderTargetAllSubimages = videoDriver->addRenderTarget();
	renderTargetAllSubimages->setTexture(renderTargetTex, renderTargetDepth);

	device->setEventReceiver(new EventReceiverForKeyboard(device, renderTargetTex));

	if (!device)
	{
		return 1;
	}

	//Set the caption of the window to some nice text. Note that there is an
	//'L' in front of the string. The Irrlicht Engine uses wide character
	//strings when displaying text.



	//===========================================================================================================================
	//===========================================================================================================================
	//===========================================================================================================================

	if (initialParametres->isCubeEnabled)
	{
		char filepath[] = "../media/cube.dae";
		IAnimatedMesh* mesh = sceneManager->getMesh(filepath);
		if (!mesh)
		{
			device->drop();
			return 1;
		}
		IAnimatedMeshSceneNode* cubeModel = sceneManager->addAnimatedMeshSceneNode(mesh);
		if (cubeModel)
		{
			cubeModel->setMaterialFlag(EMF_LIGHTING, true);
			cubeModel->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
			cubeModel->setScale(vector3df(initialParametres->cubeScale, initialParametres->cubeScale, initialParametres->cubeScale));
			cubeModel->setRotation(vector3df(initialParametres->cubeRotationX, initialParametres->cubeRotationY, initialParametres->cubeRotationZ));
			cubeModel->setPosition(vector3df(initialParametres->cubePositionX, initialParametres->cubePositionY, initialParametres->cubePositionZ));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			cubeModel->addAnimator(anim);
		}
	}

	if (initialParametres->isBunnyEnabled)
	{
		IAnimatedMesh* mesh = sceneManager->getMesh("../media/bun_zipper-blender.obj");
		if (!mesh)
		{
			device->drop();
			return 1;
		}
		IAnimatedMeshSceneNode* bunnyModel = sceneManager->addAnimatedMeshSceneNode(mesh);
		if (bunnyModel)
		{
			bunnyModel->setMaterialFlag(EMF_LIGHTING, true);
			bunnyModel->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

			bunnyModel->setScale(vector3df(initialParametres->bunnyScale, initialParametres->bunnyScale, initialParametres->bunnyScale));
			bunnyModel->setRotation(vector3df(initialParametres->bunnyRotationX, initialParametres->bunnyRotationY, initialParametres->bunnyRotationZ));
			bunnyModel->setPosition(vector3df(initialParametres->bunnyPositionX, initialParametres->bunnyPositionY, initialParametres->bunnyPositionZ));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			bunnyModel->addAnimator(anim);
		}
	}


	//Add a light source to make the cube visable.
	sceneManager->addLightSceneNode(0, core::vector3df(200, 200, 200), video::SColorf(1.0f, 1.0f, 1.0f), 2000);
	sceneManager->addLightSceneNode(0, core::vector3df(200, 200, -200), video::SColorf(1.0f, 1.0f, 1.0f), 2000);
	sceneManager->addLightSceneNode(0, core::vector3df(200, -200, -200), video::SColorf(1.0f, 1.0f, 1.0f), 2000);
	sceneManager->addLightSceneNode(0, core::vector3df(-200, 200, 200), video::SColorf(1.0f, 1.0f, 1.0f), 2000);
	sceneManager->setAmbientLight(video::SColorf(0.5f, 0.5f, 0.5f));
	//Setting the Affector and the testData will change the render parametres.
	matrix4* viewProjectionMatrixAffector = new matrix4();
	viewProjectionMatrixAffector->buildCameraLookAtMatrixLH(vector3df(0, 0, 0), vector3df(0, 0, 10), vector3df(0, 1, 0));

	ICameraSceneNode* currentCamera = sceneManager->addCameraSceneNode();
	// currentCamera->setViewMatrixAffector(*viewProjectionMatrixAffector);
	currentCamera->setViewMatrixAffector(*obliqueMatrixList->getViewMatrixByPixel(0, 19));
	currentCamera->setProjectionMatrix(*obliqueMatrixList->getProjectionMatrixByPixel(0, 19), true);
	//===========================================================================================================================
	//===========================================================================================================================
	//===========================================================================================================================

	//Enable Stencil buffer and write in it. It's used as mask in this case. ======================================
	glClearStencil(0);
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	glEnable(GL_STENCIL_TEST);



	//Decide if there is a simulator.
	static PlaneSimulator *planeSimulator = new PlaneSimulator(
		vector3df(0, 1, -3),
		initialParametres->widthOfRenderzoneByPixel,
		initialParametres->heightOfRenderzoneByPixel,
		initialParametres->widthOfSubimageByPixel,
		initialParametres->heightOfSubimageByPixel,
		initialParametres->widthOfSubimageBymm,
		initialParametres->heightOfSubimageBymm,
		initialParametres->thicknessOfTransparentMaterialBetweenDevices,
		initialParametres->refractionIndexOfTransparentMaterial,
		2,
		2
		);

	while (device->run())
	{
		//===================================================================================================
		//===================================================================================================
		//===================================================================================================
		videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, 0, 0, 0));//If it is SColor(0), the background will be transparent
		videoDriver->setRenderTargetEx(renderTargetAllSubimages, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(255, 0, 0, 0));

		for (int xInSubimageByPixel = 0; xInSubimageByPixel < initialParametres->widthOfSubimageByPixel; xInSubimageByPixel++)
		{
			for (int yInSubimageByPixel = 0; yInSubimageByPixel < initialParametres->heightOfSubimageByPixel; yInSubimageByPixel++)
			{
				glClearStencil(0);
				glClear(GL_STENCIL_BUFFER_BIT);
				glStencilFunc(GL_NEVER, 0x1, 0x1);
				glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
				//set part of the stencil buffer by drawing. It is strange that I can only draw the rects by the methods provided by irrlicht.
				for (int xSubimageCount = 0; xSubimageCount < initialParametres->xSubimageCountMax; xSubimageCount++)
				{
					for (int ySubimageCount = 0; ySubimageCount < initialParametres->ySubimageCountMax; ySubimageCount++)
					{
						videoDriver->draw2DRectangle(
							video::SColor(255, 255, 255, 255),
							core::rect<s32>(
								(initialParametres->widthOfSubimageByPixel) * xSubimageCount + xInSubimageByPixel,
								(initialParametres->heightOfSubimageByPixel) * ySubimageCount + yInSubimageByPixel,
								(initialParametres->widthOfSubimageByPixel) * xSubimageCount + xInSubimageByPixel + 1,
								(initialParametres->heightOfSubimageByPixel) * ySubimageCount + yInSubimageByPixel + 1
								)
							);
					}
				}
				glStencilFunc(GL_EQUAL, 0x1, 0x1);
				glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
				currentCamera->setViewMatrixAffector(*obliqueMatrixList->getViewMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel));
				currentCamera->setProjectionMatrix(*obliqueMatrixList->getProjectionMatrixByPixel(xInSubimageByPixel, yInSubimageByPixel), true);
				sceneManager->drawAll();
			}
		}
		//===================================================================================================
		glDisable(GL_STENCIL_TEST);
		//===================================================================================================
		for (int leftToRightCount = 0; leftToRightCount < initialParametres->xSubimageCountMax; leftToRightCount++)
		{
			videoDriver->draw2DRectangle(
				SColor(255, 0, 0, 0),
				core::rect<s32>(
					leftToRightCount * initialParametres->widthOfSubimageByPixel,
					0,
					(leftToRightCount + 1) * initialParametres->widthOfSubimageByPixel,
					initialParametres->heightOfSubimageByPixel
					)
				);
			videoDriver->draw2DRectangle(
				SColor(255, 0, 0, 0),
				core::rect<s32>(
					leftToRightCount * initialParametres->widthOfSubimageByPixel,
					(initialParametres->ySubimageCountMax - 1) * initialParametres->heightOfSubimageByPixel,
					(leftToRightCount + 1) * initialParametres->widthOfSubimageByPixel,
					(initialParametres->ySubimageCountMax) * initialParametres->heightOfSubimageByPixel
					)
				);

			if (initialParametres->widthOfSubimageByPixel % 2 == 0)
			{
				videoDriver->draw2DRectangle(
					SColor(255, 255, 255, 255),
					core::rect<s32>(
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel - 2,
						0.5 * initialParametres->heightOfSubimageByPixel - 2,
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel + 2,
						0.5 * initialParametres->heightOfSubimageByPixel + 2
						)
					);
				videoDriver->draw2DRectangle(
					SColor(255, 255, 255, 255),
					core::rect<s32>(
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel - 2,
						(initialParametres->ySubimageCountMax - 0.5) * initialParametres->heightOfSubimageByPixel - 2,
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel + 2,
						(initialParametres->ySubimageCountMax - 0.5) * initialParametres->heightOfSubimageByPixel + 2
						)
					);
			}
			else
			{
				videoDriver->draw2DRectangle(
					SColor(255, 255, 255, 255),
					core::rect<s32>(
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel - 1,
						0.5 * initialParametres->heightOfSubimageByPixel - 1,
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel + 2,
						0.5 * initialParametres->heightOfSubimageByPixel + 2
						)
					);
				videoDriver->draw2DRectangle(
					SColor(255, 255, 255, 255),
					core::rect<s32>(
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel - 1,
						(initialParametres->ySubimageCountMax - 0.5) * initialParametres->heightOfSubimageByPixel - 1,
						(leftToRightCount + 0.5) * initialParametres->widthOfSubimageByPixel + 2,
						(initialParametres->ySubimageCountMax - 0.5) * initialParametres->heightOfSubimageByPixel + 2
						)
					);
			}

		}
		//===================================================================================================
		//===================================================================================================
		videoDriver->setRenderTargetEx(0, 0, SColor(0));

		if (initialParametres->isSimulating)
		{
			for (int xSubimageCount = 0; xSubimageCount < initialParametres->xSubimageCountMax; xSubimageCount++)
			{
				for (int ySubimageCount = 0; ySubimageCount < initialParametres->ySubimageCountMax; ySubimageCount++)
				{
					//videoDriver->draw2DRectangle(
					//	video::SColor(255, 255, 255, 255),
					//	core::rect<s32>(
					//		(initialParametres->widthOfSubimageByPixel) * (xSubimageCount + 0.5) - 1,
					//		(initialParametres->heightOfSubimageByPixel) * (ySubimageCount + 0.5) - 1,
					//		(initialParametres->widthOfSubimageByPixel) * (xSubimageCount + 0.5) + 1,
					//		(initialParametres->heightOfSubimageByPixel) * (ySubimageCount + 0.5) +1
					//		)
					//	);
					//videoDriver->draw2DRectangle(
					//	video::SColor(255, 0, 0, 0),
					//	core::rect<s32>(
					//		planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).X,
					//		planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).Y,
					//		planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).X + 2,
					//		planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).Y + 2
					//		)
					//	);
					videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(((xSubimageCount + 0.5) * initialParametres->widthOfSubimageByPixel - 1), ((ySubimageCount + 0.5) * initialParametres->heightOfSubimageByPixel - 1)),
						core::rect<s32>(
							planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).X,
							planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).Y,
							planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).X + 2,
							planeSimulator->getCoorinatesInSubimage(xSubimageCount, ySubimageCount).Y + 2
							),
						0,
						video::SColor(255, 255, 255, 255), true);
				}
			}
			guiEnvironment->drawAll();
		}
		else
		{
			videoDriver->draw2DImage(renderTargetTex, core::position2d<s32>(0, 0),
				core::rect<s32>(
					0,
					0,
					initialParametres->widthOfRenderzoneByPixel,
					initialParametres->heightOfRenderzoneByPixel
					),
				0,
				video::SColor(255, 255, 255, 255), true);
		}

		if (initialParametres->isSingleFrameRenderingAndQuitMode)
		{
			savetex(renderTargetTex, "SingleFrameRenderingResult.png", videoDriver);
			break;
		}

		glEnable(GL_STENCIL_TEST);
		videoDriver->endScene();
	}
	//=================================================================================
	//=================================================================================
	//=================================================================================


	//End by deleting the device.
	device->drop();
	return 0;
}
