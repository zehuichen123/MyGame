//this is a UI control widget
//when the snail reach the destination,
//then you pass this level successfully !

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
	
	CC_SYNTHESIZE(float, runTime, RunTime);
	
private:
	
	bool setUpdateView();
	Sprite* snailBg;
	Sprite* snail;
	ProgressTimer* SnailBar;

};
