#include "Role.h"

Role::Role() :
	_idleAction(NULL),
	_walkAction(NULL),
	_hurtAction(NULL),
	_normalAttackAction(NULL),
	_skillAttackAction(NULL),
	_deadAction(NULL),
	currActionState(ACTION_STATE_NONE)
{};
Role::~Role(){}

void Role::runIdleAction()
{
	if (ChangeState(ACTION_STATE_IDLE))
	{
		this->runAction(_idleAction);
	}
}

void Role::runWalkAction()
{
	if (ChangeState(ACTION_STATE_WALK))
	{
		this->runAction(_walkAction);
	}
}
void Role::runNormalAttackAction()
{
	if (ChangeState(ACTION_STATE_NORMAL_ATTACK))
	{
		this->runAction(_normalAttackAction);
	}
}

void Role::runSkillAction()
{
	if (ChangeState(ACTION_STATE_SKILL_ATTACK))
	{
		this->runAction(_skillAttackAction);
	}
}

void Role::runDeadAction()
{
	if (ChangeState(ACTION_STATE_DEAD))
	{
		this->runAction(_deadAction);
	}
}

void Role::runHurtAction()
{
	if (ChangeState(ACTION_STATE_HURT))
	{
		this->runAction(_hurtAction);
	}
}

Animation* Role::createAttackAnimation(const char* formatStr,int FrameCountBegin,int FrameCountEnd,int fps)
{
	Vector<SpriteFrame*>pFrames;
	for (int i = FrameCountBegin; i < FrameCountEnd; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		//pFrames.insert(i-FrameCountBegin,pFrame);
		//if i use pushBack(),what will happen?
		pFrames.pushBack(pFrame);
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
		pFrames.pushBack(pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

bool Role::ChangeState(ActionState actionState)
{
	if (currActionState == ACTION_STATE_DEAD || currActionState == actionState)
	{
		return false;
	}
	this->stopAllActions();
	this->currActionState = actionState;
	return true;
}

BoundingBox Role::createBoundingBox(Vec2 Origin,Size size)
{
	BoundingBox boundingBox;
	boundingBox.actual.origin = Origin+this->getPosition();
	boundingBox.actual.size = size;
	boundingBox.original.origin = Origin;
	boundingBox.original.size = size;
	return boundingBox;
}

//don't know the exact meaning
void Role::updateBoxes()
{
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if (isFlippedX)
	{
		x = this->getPosition().x - _hitBox.original.origin.x;
	}
	else
	{
		x = this->getPosition().x + _hitBox.original.origin.x;
	}
	_hitBox.actual.origin = Vec2(x, this->getPosition().y + _hitBox.original.origin.y);
	_bodyBox.actual.origin = this->getPosition() + _bodyBox.original.origin;
}

void Role::setPosition(const Vec2 &position)
{
	Sprite::setPosition(position);
	this->updateBoxes();
}

CallFunc* Role::createIdleCallBackFunc()
{
	this->setAllowMove(true);
	return CallFunc::create(CC_CALLBACK_0(Role::runIdleAction, this));
}
