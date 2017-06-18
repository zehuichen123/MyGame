//it is a derive class 
//which will be inherted by 
//other classes like defenderGameLayer

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BaseLayer :public Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BaseLayer);
	Size getWinSize();
	Point getWinOrigin();
	Point getWinCenter();
};