#pragma once
#include "cocos2d.h"
#include "cityBloodSprite.h"
USING_NS_CC;
class snailBar :public Node {
public:
	snailBar();
	~snailBar();
	static snailBar* createPic();
	void runSnailAnimation();
	void gameCallBack(Node * pSender);
	//void setSnailProgress(float progress);
	CC_SYNTHESIZE(float, runTime, RunTime);
	//void initialization();
private:
	bool setUpdateView();
	Sprite* snailBg;
	ProgressTimer* SnailBar;
	Sprite* snail;
};