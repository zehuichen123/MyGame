#pragma once
#include "cocos2d.h"
USING_NS_CC;
typedef struct BoundingBox {
	Rect actual;
	Rect original;
}BoundingBox;
typedef enum {
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_NORMAL_ATTACK,
	ACTION_STATE_SKILL_ATTACK,
	ACTION_STATE_HURT,
	ACTION_STATE_DEAD
}ActionState;
class Role :public Sprite {
public:
	Role();
	~Role();

	//set some characters to role
	CC_SYNTHESIZE(float, curLifeValue, curLifeValue);
	CC_SYNTHESIZE(float, LifeValue, LifeValue);
	CC_SYNTHESIZE(ActionState, currActionState, CurrActionState);
	CC_SYNTHESIZE(bool, allowMove, AllowMove);
	CC_SYNTHESIZE(Vec2, velocity, Velocity);
	CC_SYNTHESIZE(float, damageStrength, DamageStrength);

	//create animation list
	CC_SYNTHESIZE_RETAIN(Action*, _idleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(Action*, _hurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(Action*, _normalAttackAction, NormalAttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, _skillAttackAction, SkillAttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, _deadAction, DeadAction);


	//
	BoundingBox createBoundingBox(Vec2 Original, Size size);
	CC_SYNTHESIZE(BoundingBox, _bodyBox, BodyBox);
	CC_SYNTHESIZE(BoundingBox, _hitBox, HitBox);
	
public:
	//execute after executing actions
	void Role::callBackAction(Node* pSender);

	virtual void runIdleAction();
	virtual void runWalkAction();
	virtual void runNormalAttackAction();
	virtual void runSkillAction();
	virtual void runHurtAction();
	virtual void runDeadAction();

	//call idle animation after run above actions
	CallFunc* createIdleCallBackFunc();

	virtual void setPosition(const Vec2& Position);

	void updateBoxes();

protected:
	virtual Animation* createNormalAnimation(const char* formatStr, int frameCount, int fps);
	virtual Animation* createAttackAnimation(const char* formatStr, int frameCountBegin,int frameCountEnd, int fps);

private:
	virtual bool ChangeState(ActionState actionState);
};