#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
class welcomeLayer :public BaseLayer {
public:
	welcomeLayer();
	~welcomeLayer();
	virtual bool init();
	virtual void onEnter();
	static Scene* createScene();
	CREATE_FUNC(welcomeLayer);
	bool isEffect;
private:
	bool setUpdateView();
	void videoCallBack(Ref* pSender);
	void clickCallBack(Ref* pSender);
};