#pragma once
#include "cocos2d.h"
#include "magicSkillButton.h"
#include "Global.h"
USING_NS_CC;
class skillButtonLayer:public Layer {
public:
	skillButtonLayer();
	~skillButtonLayer();
	CREATE_FUNC(skillButtonLayer);
	CC_SYNTHESIZE(int, type, Type);
	void onTouchEnded(Touch* touch, Event* event);
	void onEnter();
	bool init();
private:
	Sprite* matrix;
	magicSkillButton* cdButtonOne;
	magicSkillButton* cdButtonTwo;
	magicSkillButton* cdButtonThree;
	
};