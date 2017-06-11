#pragma once
#include "cocos2d.h"
USING_NS_CC;
class snailBar :public Node {
public:
	snailBar();
	~snailBar();
	static snailBar* createPic();
	void runSnailAnimation();
	void setSnailProgress(float progress);
	CC_SYNTHESIZE(float, runTime, RunTime);
	void initialization();
private:
	bool setUpdateView();
	Sprite* snailBg;
	ProgressTimer* SnailBar;
	Sprite* snail;
};