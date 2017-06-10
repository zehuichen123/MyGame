#pragma once
#include "cocos2d.h"
#include "Role.h"
//#include "Global.h"
USING_NS_CC;
class magicSkillButton :public Sprite {
public:
	magicSkillButton();
	~magicSkillButton();
	static magicSkillButton* create(char* Icon);
	CC_SYNTHESIZE(float, hurt, Hurt);
	CC_SYNTHESIZE(bool, avail, Avail);
	//CC_SYNTHESIZE(bool, activation, Activation);
	//CC_PROPERTY(bool, activation, Activation);
	CC_SYNTHESIZE(float, cost, Cost);
	void runCDAnimation();
	void cdCallBack(Node* pSender);
	void runSkillAnimationA(Layer* layer,Point point);
	void runSkillAnimationB(Layer* layer,Point point);
	void runSkillAnimationC(Layer* layer,Point point);
	void detected(Point point);
private:
	void skillCallBack(Node* pSender);
	//Animation * createNormalAnimation(const char * formatStr, int FrameCount, int fps);
	ProgressTimer* cdBar;
	Sprite* cdIcon;
	bool setUpdateView(char* Icon);
};