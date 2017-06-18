//this is a sprite to show your life 
//and the remain blue bar

#pragma once
#include "cocos2d.h"
#include "Global.h"
#include "GameSuccessfullyLayer.h"
#include "gameOverLayer.h"
USING_NS_CC;
class cityBloodSprite :public Sprite {
public:
	cityBloodSprite();
	~cityBloodSprite();
	void beAttack(float hurt);
	bool magicCost(float value);			//the cost of using skill once
	void recoverMagic(float dt);			//recover the blue bar by time
	static cityBloodSprite* create();
	
	CC_SYNTHESIZE(float, cityBlood, CityBlood);
	CC_SYNTHESIZE(float, magicValue, MagicValue);
private:
	bool setUpdateView();

	ProgressTimer* bloodBar;
	ProgressTimer* magicBar;
};