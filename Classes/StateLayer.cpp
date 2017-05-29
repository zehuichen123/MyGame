#include "StateLayer.h"
StateLayer::StateLayer()
{
	global->stateLayer = this;
}
StateLayer::~StateLayer(){}
bool StateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		//add code here.
		//auto hpShow = Hpshow::create();
		//this->addChild(hpShow);
		ret = true;
	} while (0);
	return ret;
}