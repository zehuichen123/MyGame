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
	//void onEnter();
	//virtual bool onTouchBegan(Touch* touch, Event* event);
	//virtual void onTouchEnded(Touch* touch, Event* evnet);
	CREATE_FUNC(GamePause);
	bool setUpdateView();
private:
	void homeCallBack(Ref* pSender);
	void resumeCallBack(Ref* pSender);
	void retryCallBack(Ref* pSender);

};