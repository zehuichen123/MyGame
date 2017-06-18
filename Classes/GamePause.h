//this is a game pause interface 
//we use popupLayer to show it

#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "welcomeLayer.h"
USING_NS_CC;
class GamePause :public BaseLayer {
public:
	GamePause();
	~GamePause();
	virtual bool init();
	CREATE_FUNC(GamePause);
	
private:
	void homeCallBack(Ref* pSender);
	void resumeCallBack(Ref* pSender);
	void retryCallBack(Ref* pSender);
	bool setUpdateView();
};