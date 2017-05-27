#include "MapLayer.h"
MapLayer::MapLayer() {};
MapLayer::~MapLayer() {};
bool MapLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());

		

		ret = true;
	} while (0);
	this->scheduleUpdate();
	return ret;
}
