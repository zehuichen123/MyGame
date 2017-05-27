#include "OperateLayer.h"
OperateLayer::OperateLayer(){}
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