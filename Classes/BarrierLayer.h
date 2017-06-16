#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BarrierLayer :public Layer {
public:
	BarrierLayer();
	~BarrierLayer();
	bool init();
	CREATE_FUNC(BarrierLayer);
};