//Enemy is a class inherited from Role

#pragma once
#include "cocos2d.h"
#include "Role.h"
#include "Global.h"
USING_NS_CC;

class Enemy :public Role {

public:

	Enemy();
	~Enemy();

	bool setUpdateView();
	bool init();
	void update(float dt);
	bool beAttacked();
	bool beSkillAttack();
	void runWalkAction();
	void runNormalAttackAction();
	void runDeadAction();
	void monsterMoveFinished(Ref* pSender);
	void Move();	
	CREATE_FUNC(Enemy);
private:

	ProgressTimer* bloodValue;

	void attackCallBackAction(float dt);
	void deadCallBackAction(Node* pSender);
};