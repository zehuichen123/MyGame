#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class cityBloodSprite :public Sprite {
public:
	static cityBloodSprite* create();
	cityBloodSprite();
	~cityBloodSprite();
	CC_SYNTHESIZE(float, cityBlood, CityBlood);
	CC_SYNTHESIZE(float, magicValue, MagicValue);
	void beAttack(float hurt);
	bool magicCost(float value);

	void recoverMagic(float dt);

	
private:
	bool setUpdateView();
	ProgressTimer* bloodBar;
	ProgressTimer* magicBar;
};