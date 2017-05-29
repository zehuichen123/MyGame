#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class StateLayer :public Layer {
public:
	StateLayer();
	~StateLayer();
	virtual bool init();
};