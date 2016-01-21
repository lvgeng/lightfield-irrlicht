#pragma once
#include <irrlicht.h>
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventReceiverForEsc : public IEventReceiver
{
private:
	IrrlichtDevice *deviceInner;
public:
	bool OnEvent(const SEvent& event);
	EventReceiverForEsc(IrrlichtDevice* device);
	~EventReceiverForEsc();
};