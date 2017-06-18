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
	CC_SYNTHESIZE(int, type, Type);     //distinguish the button type(3)

	bool onTouchBegan(Touch * touch, Event * event);
	void onTouchEnded(Touch* touch, Event* event);
	void onEnter();
	bool init();
	void detected(__Array* enemy);

private:

	Sprite* matrix;
	magicSkillButton* cdButtonOne;
	magicSkillButton* cdButtonTwo;
	magicSkillButton* cdButtonThree;
};