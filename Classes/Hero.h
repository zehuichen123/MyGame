#pragma once
#include "cocos2d.h"
#include "Role.h"
#include "Global.h"
USING_NS_CC;
class Hero :public Role {
public:
	Hero();
	~Hero();
	virtual bool init();
	CREATE_FUNC(Hero);
	void onMove(Vec2 direction, float distance);
	void onStop();
	void onAttack();
	void updateSelf();
	void Hero::attackCallBackAction(Ref* pSender);
	void Hero::skillCallBackAction(Ref* pSender);
};