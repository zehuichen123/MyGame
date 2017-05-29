#include "OperateLayer.h"
OperateLayer::OperateLayer()
{
	global->operateLayer = this;
}
OperateLayer::~OperateLayer(){}
bool OperateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		//add code here.

		ret = true;
	} while (0);
	return ret;
}