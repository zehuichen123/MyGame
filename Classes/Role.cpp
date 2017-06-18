#include "Role.h"

/* change the current stastics of the role in this level*/
Role::Role() :
	curLifeValue(100),
	LifeValue(100),
	damageStrength(1),
	weaponHurt(55),
	defense(0.0),
	skillHurt(300),
	speed(150),

	_walkAction(NULL),
	_normalAttackAction(NULL),
	_deadAction(NULL)
{
	//improve enemy's defensive power
	auto originDefense = this->getDefense();
	this->setDefense(originDefense+ChangeSystem::defendImprove());

	//improve enemy's ATK
	auto originHurt = this->getDamageStrength();
	this->setDamageStrength(originHurt + ChangeSystem::hurtImprove());

	//improve enemy's move speed
	auto originSpeed = this->getSpeed();
	this->setSpeed(originSpeed + ChangeSystem::speedImprove());
};
Role::~Role()
{
	CC_SAFE_RELEASE_NULL(_walkAction);
	CC_SAFE_RELEASE_NULL(_normalAttackAction);
	CC_SAFE_RELEASE_NULL(_deadAction);
}

Animation* Role::createNormalAnimation(const char* formatStr, int FrameCount, int fps)
{
	Vector<SpriteFrame*>pFrames;
	for (int i = 0; i < FrameCount; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i , pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

