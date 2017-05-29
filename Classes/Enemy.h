/*this class is similar to Hero,
	so i won't give too much annotation*/

#pragma once
#include "cocos2d.h"
#include "Role.h"
#include "Global.h"
USING_NS_CC;

typedef enum {
	AI_IDLE=0,
	AI_PATROL,
	AI_ATTACK,
	AI_PURSUE
}AiState;

class Enemy :public Role {

public:
	Enemy();
	~Enemy();
	bool init();
	void updateSelf();
	CREATE_FUNC(Enemy);
	
	CC_SYNTHESIZE(Vec2, m_moveDirection, MoveDirection);
	CC_SYNTHESIZE(float, m_eyeArea, EyeArea);
	CC_SYNTHESIZE(float, m_attackArea, AttackArea);
	CC_SYNTHESIZE(AiState, m_aiState, AiState);
	void attackCallBackAction(Node* pSender);

private:
	void decide(const Vec2 &target, float targetWidth);
	void execute(const Vec2 &target, float targetWidth);
	unsigned int m_nextDecisionTime;

};