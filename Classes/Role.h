#pragma once
#include "cocos2d.h"
#include "ChangeSystem.h"
USING_NS_CC;
class Role :public Sprite {
public:
	Role();
	~Role();

	//set some characters to role
	CC_SYNTHESIZE(float, curLifeValue, curLifeValue);
	CC_SYNTHESIZE(float, LifeValue, LifeValue);
	//CC_SYNTHESIZE(bool, allowMove, AllowMove);
	CC_SYNTHESIZE(float, damageStrength, DamageStrength);
	CC_SYNTHESIZE(float, defense, Defense);
	CC_SYNTHESIZE(float, weaponHurt, WeaponHurt);
	CC_SYNTHESIZE(float, skillHurt, SkillHurt);
	CC_SYNTHESIZE(float, speed, Speed);

	//create animation list
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(Action*, _normalAttackAction, NormalAttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, _deadAction, DeadAction);


public:
	//virtual void runIdleAction();
	static Animation* createNormalAnimation(const char* formatStr, int frameCount, int fps);
	static Animation* createAttackAnimation(const char* formatStr, int frameCountBegin,int frameCountEnd, int fps);

};