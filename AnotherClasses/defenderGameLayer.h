#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
USING_NS_CC;
class defenderGameLayer :public BaseLayer {
public:
	defenderGameLayer() {}
	~defenderGameLayer() {}
	virtual bool init();
	void onEnter();
	CREATE_FUNC(defenderGameLayer);
	//virtual bool onTouchBegan(Touch* touch, Event* event);
	//virtual void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void bulletMoveFinished(Ref * pSender);
	virtual void onTouchCancelled(Touch* touch, Event* event);
	float getRotaSize(Touch* touch);
	void updateCustom(float dt);
	static Scene* createScene();
private:
	bool setUpdateView();
	void detect(float tim);
	void weaponCallBack(Ref* pSender);
	Sprite* weapon;
	Sprite* bulletSample;
};