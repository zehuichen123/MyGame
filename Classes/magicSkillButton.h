//this is skillButton class,
//realize the function cd cool down animation

#pragma once
#include "cocos2d.h"
#include "Role.h"
USING_NS_CC;
class magicSkillButton :public Sprite {
public:

	magicSkillButton();
	~magicSkillButton();

	CC_SYNTHESIZE(float, hurt, Hurt);				//skill's ATK
	CC_SYNTHESIZE(bool, avail, Avail);				//if the cool down proccess has finished
													//in other word,if the skillButton can be touched
	CC_SYNTHESIZE(float, cost, Cost);				//the blue bar cost of using skill

	static magicSkillButton* create(char* Icon);
	void runCDAnimation();
	void runSkillAnimationA(Layer* layer,Point point);
	void runSkillAnimationB(Layer* layer,Point point);
	void runSkillAnimationC(Layer* layer,Point point);
	void detected(Point point);
private:

	bool setUpdateView(char* Icon);
	void skillCallBack(Node* pSender);
	void cdCallBack(Node* pSender);

	ProgressTimer* cdBar;
	Sprite* cdIcon;
};