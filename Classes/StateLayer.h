#pragma once
#include "cocos2d.h"
#include "Global.h"
#include "HpShow.h"
USING_NS_CC;
class StateLayer :public Layer {
public:
	StateLayer();
	~StateLayer();
	virtual bool init();
	CREATE_FUNC(StateLayer);
};