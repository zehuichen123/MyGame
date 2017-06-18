//if you pass one level successfully,
//you will see this scene which is 
//a settlement page

#pragma once
#ifndef __GAMESUCCESSFULLY_LAYER_H__
#define __GAMESUCCESSFULLY_LAYER_H__
#include "BaseLayer.h"
USING_NS_CC;
class GameSuccessfullyLayer :public BaseLayer {
public:
	GameSuccessfullyLayer();
	~GameSuccessfullyLayer();
	static Scene* createScene();
	CREATE_FUNC(GameSuccessfullyLayer);
	virtual bool init();
	void onEnter();
	void onExit();
	virtual bool onTouchBegan(Touch *touch,Event *event);
private:
	bool setUpdateView();
};
#endif