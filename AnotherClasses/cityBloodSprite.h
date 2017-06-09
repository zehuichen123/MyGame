#pragma once
#include "cocos2d.h"
USING_NS_CC;
class cityBloodSprite :public Sprite {
public:
	static cityBloodSprite* create();
	cityBloodSprite();
	~cityBloodSprite();

	CC_SYNTHESIZE(float, cityBlood, CityBlood);
	CC_SYNTHESIZE(float, magicValue, MagicValue);
private:
	bool setUpdateView();
	ProgressTimer* bloodBar;
	ProgressTimer* magicBar;
};