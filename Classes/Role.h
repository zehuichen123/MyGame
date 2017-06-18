#pragma once
#include "cocos2d.h"
#include "ChangeSystem.h"
USING_NS_CC;
class Role :public Sprite {
public:

	Role();
	~Role();

	//set some attributes to role
	CC_SYNTHESIZE(float, curLifeValue, curLifeValue);			//enemy's current life value
	CC_SYNTHESIZE(float, LifeValue, LifeValue);					//enemy's total life value
	CC_SYNTHESIZE(float, damageStrength, DamageStrength);		//enemy's ATK
	CC_SYNTHESIZE(float, defense, Defense);						//enemy's defensive power	
	CC_SYNTHESIZE(float, speed, Speed);							//enmey's move speed
	CC_SYNTHESIZE(float, weaponHurt, WeaponHurt);				//your arrow's ATK
	CC_SYNTHESIZE(float, skillHurt, SkillHurt);					//your skill's ATK

	//create animation list for enemy
	CC_SYNTHESIZE_RETAIN(Action*, _walkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(Action*, _normalAttackAction, NormalAttackAction);
	CC_SYNTHESIZE_RETAIN(Action*, _deadAction, DeadAction);

public:

	static Animation* createNormalAnimation(const char* formatStr, int frameCount, int fps);

};