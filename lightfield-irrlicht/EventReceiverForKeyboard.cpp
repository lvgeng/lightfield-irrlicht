#include "EventReceiverForKeyboard.h"

bool EventReceiverForKeyboard::OnEvent(const SEvent & event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE && event.KeyInput.PressedDown)
	{
		deviceInner->closeDevice();
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_1  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot1.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_2  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot2.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_3  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot3.png");
		return true;
	}
}

EventReceiverForKeyboard::EventReceiverForKeyboard(IrrlichtDevice* device)
{
	deviceInner = device;
}


EventReceiverForKeyboard::~EventReceiverForKeyboard()
{
}
