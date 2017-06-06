#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "welcomeLayer.h"
USING_NS_CC;
class LoadingLayer :public BaseLayer {
public:
	LoadingLayer();
	~LoadingLayer();
	bool init();
	static Scene* createScene();
	void loadCallBack();
	void goWelcomeLayer();
	CREATE_FUNC(LoadingLayer);
private:
	int loadingNum;
	int totalNum;
	ProgressTimer* loadingProcess;
	bool setUpdateView();
};