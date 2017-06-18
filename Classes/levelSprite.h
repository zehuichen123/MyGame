//show the current level

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class levelSprite :public Sprite {
public:
	levelSprite();
	~levelSprite();
	static levelSprite* createNum();
	void setLevelNum(int num);
	void runLevelShowAnimation();
	
private:
	void levelShowCallBack(Node* pSender);
	bool setUpdateView();

};