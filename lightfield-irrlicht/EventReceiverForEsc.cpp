#include "EventReceiverForEsc.h"

bool EventReceiverForEsc::OnEvent(const SEvent & event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE && event.KeyInput.PressedDown)
	{
		deviceInner->closeDevice();
		return true;
	}
}

EventReceiverForEsc::EventReceiverForEsc(IrrlichtDevice* device)
{
	deviceInner = device;
}


EventReceiverForEsc::~EventReceiverForEsc()
{
}
