#pragma once
#include <irrlicht.h>
#include <string>
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventReceiverForKeyboard : public IEventReceiver
{
private:
	IrrlichtDevice *deviceInner;
	video::ITexture* renderTargetTexInner;
	void savetex(ITexture *texture, std::string filename, IVideoDriver* videoDriver);
public:
	bool OnEvent(const SEvent& event);
	EventReceiverForKeyboard(IrrlichtDevice* device, video::ITexture* renderTargetTex);
	~EventReceiverForKeyboard();
};
