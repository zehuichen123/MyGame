/*this class is similar to Hero,
	so i won't give too much annotation*/

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
	void updateSelf();
	void update(float dt);
	CREATE_FUNC(Enemy);

	CC_SYNTHESIZE(float, actualDuration, ActualDuration);
	
	bool beAttacked();

	void beSkillAttack();

	void runWalkAction();
	void runNormalAttackAction();
	void runDeadAction();
	void monsterMoveFinished(Ref* pSender);
	void Move();
	//void underAttack();
private:
	ProgressTimer* bloodValue;
	void attackCallBackAction(Node* pSender);
	void deadCallBackAction(Node* pSender);
};