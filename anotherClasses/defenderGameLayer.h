#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "Enemy.h"
#include "Global.h"
#include "GamePause.h"
#include "PopupLayer.h"
#include "cityBloodSprite.h"
USING_NS_CC;
class defenderGameLayer :public BaseLayer {
public:
	defenderGameLayer() {}
	~defenderGameLayer() {}
	virtual bool init();
	void onEnter();
	void update(float dt);
	void pauseCallBack(Ref * pSender);
	CREATE_FUNC(defenderGameLayer);
	//virtual bool onTouchBegan(Touch* touch, Event* event);
	//virtual void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void bulletMoveFinished(Ref * pSender);
	virtual void onTouchCancelled(Touch* touch, Event* event);
	float getRotaSize(Touch* touch);
	void updateCustom(float dt);
	static Scene* createScene();
	void addEnemy(float dt);
private:
	__Array* _enemy;
	__Array* _bullet;
	__Array* toDeleteEnemy;
	__Array* toDeleteBullet;
	bool setUpdateView();
	void detect(float tim);
	void weaponCallBack(Ref* pSender);
	//Sprite* target;
	Sprite* weapon;
	Sprite* bulletSample;
};