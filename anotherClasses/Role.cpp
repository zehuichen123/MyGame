#include "Role.h"

Role::Role() :
	//_idleAction(NULL),
	_walkAction(NULL),
	//_hurtAction(NULL),
	_normalAttackAction(NULL),
	//_skillAttackAction(NULL),
	_deadAction(NULL),
	//currActionState(ACTION_STATE_NONE)
	curLifeValue(100),
	LifeValue(100),
	defense(0),
	//attackRange()
	weaponHurt(50)
{};
Role::~Role()
{
	//CC_SAFE_RELEASE_NULL(_idleAction);
	CC_SAFE_RELEASE_NULL(_walkAction);
	CC_SAFE_RELEASE_NULL(_normalAttackAction);
	//CC_SAFE_RELEASE_NULL(_skillAttackAction);
	//CC_SAFE_RELEASE_NULL(_hurtAction);
	CC_SAFE_RELEASE_NULL(_deadAction);
}


Animation* Role::createAttackAnimation(const char* formatStr,int FrameCountBegin,int FrameCountEnd,int fps)
{
	Vector<SpriteFrame*>pFrames;
	for (int i = FrameCountBegin; i < FrameCountEnd; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i - FrameCountBegin, pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
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

