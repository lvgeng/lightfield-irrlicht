#include <irrlicht.h>
#include <GL/freeglut.h>
#include "ObliqueProjectionMatrixList.h"
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

int main()
{

	//The data use for initializing. It is static since there is no need to update after initializing.
	static InitialParametres *initialParametres = new InitialParametres("setting.xml");
	//The oblique projection matrix list. Only related to the projection configuration.
	static ObliqueProjectionMatrixList* obliqueProjectionMatrixList = new ObliqueProjectionMatrixList(
		initialParametres->widthOfProjectionPanelInScene,					//Width in scene. Relative.
		initialParametres->heightOfProjectionPanelInScene,					//Height in scene. Relative.
		initialParametres->widthOfSubimageByPixel,							//Width of the subimage. (pixel)
		initialParametres->heightOfSubimageByPixel,							//Height of the subimage. (pixel)
		initialParametres->widthOfSubimageBymm,								//Width of the subimage. (mm)
		initialParametres->heightOfSubimageBymm,							//Height of the subimage. (mm)
		initialParametres->thicknessOfTransparentMaterialBetweenDevices,	//Thickness of the transparent material between the light barriers and the screen. It will affect the result because of the refraction.
		initialParametres->refractionIndexOfTransparentMaterial				//Rafraction index of the transparent material.
		);

	IrrlichtDevice *device =
		createDevice(
			video::EDT_OPENGL,				//- deviceType: Type of the device. This can currently be the Null-device,one of the two software renderers, D3D8, D3D9, or OpenGL.In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			//video::EDT_DIRECT3D9,
			dimension2d<u32>(initialParametres->widthOfDisplayzoneByPixel, initialParametres->heightOfDisplayzoneByPixel),
											//- windowSize: Size of the Window or screen in FullScreenMode to be created.
			16,								//- bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			initialParametres->isFullscreen,//- fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			true,							//- stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			true,							//- vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			0								//- eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
			);
	device->setEventReceiver(new EventReceiverForKeyboard(device));

	if (!device)
	{
		return 1;
	}

	//Set the caption of the window to some nice text. Note that there is an
	//'L' in front of the string. The Irrlicht Engine uses wide character
	//strings when displaying text.
	device->setWindowCaption(L"Light field display");

	IVideoDriver* videoDriver = device->getVideoDriver();
	ISceneManager* sceneManager = device->getSceneManager();
	IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

	if (initialParametres->isCubeEnabled)
	{
		//Add a cube for the following test. Easier to figure out the problems while dealing with a simple model.
		 /*IMeshSceneNode* cubeForTest = sceneManager->addCubeSceneNode(1);
		 cubeForTest->setScale(vector3df(1, 1, 1));
		 cubeForTest->setRotation(vector3df(0, 30, 0));
		 cubeForTest->setPosition(vector3df(0,0,0.7));
		 cubeForTest->setMaterialFlag(irr::video::EMF_LIGHTING, true);
		 if (initialParametres->isTestSubjectSpinning)
		 {
		 	scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
		 		core::vector3df(0, 0.3f, 0));
		 	cubeForTest->addAnimator(anim);
		 }*/
		IAnimatedMesh* mesh = sceneManager->getMesh("../media/cube.dae");
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
			cubeModel->setScale(vector3df(0.3, 0.3, 0.3));
			cubeModel->setRotation(vector3df(0, 30, 0));
			cubeModel->setPosition(vector3df(0, 0, 0.7));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			cubeModel->addAnimator(anim);
		}
	}

	if (initialParametres->isFighterEnabled)
	{
		IAnimatedMesh* mesh = sceneManager->getMesh("../media/f14/f14d.obj");
		if (!mesh)
		{
			device->drop();
			return 1;
		}
		IAnimatedMeshSceneNode* fighterModel = sceneManager->addAnimatedMeshSceneNode(mesh);
		if (fighterModel)
		{
			fighterModel->setMaterialFlag(EMF_LIGHTING, true);
			fighterModel->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
			fighterModel->setScale(vector3df(0.1, 0.1, 0.1));
			fighterModel->setRotation(vector3df(0, 135, 0));
			fighterModel->setPosition(vector3df(0, 0.15, 0));
		}
		if (initialParametres->isTestSubjectSpinning)
		{
			scene::ISceneNodeAnimator* anim = sceneManager->createRotationAnimator(
				core::vector3df(0, 0.3f, 0));
			fighterModel->addAnimator(anim);
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
	currentCamera->setViewMatrixAffector(*viewProjectionMatrixAffector);
	currentCamera->setProjectionMatrix(*obliqueProjectionMatrixList->getProjectionByPixel(0, 19), true);

	//Decide if there is a simulator.
	if (initialParametres->isSimulating)
	{
		static PlaneSimulator *planeSimulator = new PlaneSimulator(
			vector3df(0, 1, -3),
			initialParametres->widthOfDisplayzoneByPixel,
			initialParametres->heightOfDisplayzoneByPixel,
			initialParametres->widthOfSubimageByPixel,
			initialParametres->heightOfSubimageByPixel,
			initialParametres->widthOfSubimageBymm,
			initialParametres->heightOfSubimageBymm,
			initialParametres->thicknessOfTransparentMaterialBetweenDevices,
			initialParametres->refractionIndexOfTransparentMaterial,
			2,
			2
			);
		video::IRenderTarget* simulatorRenderTarget = 0;
		video::ITexture* renderTargetTex = 0;
		scene::ICameraSceneNode* fixedCam = 0;
		renderTargetTex = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(initialParametres->widthOfDisplayzoneByPixel, initialParametres->heightOfDisplayzoneByPixel), "RTT1", video::ECF_A8R8G8B8);
		video::ITexture* renderTargetDepth = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(initialParametres->widthOfDisplayzoneByPixel, initialParametres->heightOfDisplayzoneByPixel), "DepthStencil", video::ECF_D24S8);
		simulatorRenderTarget = videoDriver->addRenderTarget();
		simulatorRenderTarget->setTexture(renderTargetTex, renderTargetDepth);

		//Enable Stencil buffer and write in it. It's used as mask in this case. ======================================
		glClearStencil(0);
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// glMatrixMode(GL_MODELVIEW);
		// glLoadIdentity();
		glEnable(GL_STENCIL_TEST);

		while (device->run())
		{
			videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, SColor(0));
			videoDriver->setRenderTargetEx(simulatorRenderTarget, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(0));

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
					currentCamera->setProjectionMatrix(*obliqueProjectionMatrixList->getProjectionByPixel(xInSubimageByPixel, yInSubimageByPixel), true);
					sceneManager->drawAll();
				}
			}
			videoDriver->setRenderTargetEx(0, 0, SColor(0));
			glDisable(GL_STENCIL_TEST);

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

			glEnable(GL_STENCIL_TEST);
			videoDriver->endScene();
		}
	}
	else
	{
		//Enable Stencil buffer and write in it. It's used as mask in this case. ======================================
		glClearStencil(0);
		glEnable(GL_STENCIL_TEST);

		while (device->run())
		{

			videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, video::SColor(0));
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
					currentCamera->setProjectionMatrix(*obliqueProjectionMatrixList->getProjectionByPixel(xInSubimageByPixel, yInSubimageByPixel), true);
					//currentCamera->setProjectionMatrix(*obliqueProjectionMatrixList->getProjectionByPixel(7,7), true);
					sceneManager->drawAll();
				}
			}
			guiEnvironment->drawAll();
			videoDriver->endScene();
		}
	}
	//End by deleting the device.
	device->drop();
	return 0;
}
