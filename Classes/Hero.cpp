#include "Hero.h"
Hero::Hero()
{
	global->hero = this;
}
Hero::~Hero()
{
}
bool Hero::init()
{
	bool ret = false;
	do {
		this->initWithSpriteFrameName("boy_idle_00.png");
		//this->setAnchorPoint(Vec2(0.48f, 0.13f));

		Animation *idleAnim = this->createNormalAnimation("boy_idle_%02d.png", 3, 5);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		Animation *walkAnim = this->createNormalAnimation("boy_run_%02d.png", 8, 12);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		Animation *attackAnima1 = this->createAttackAnimation("boy_attack_00_%02d.png", 0, 4, 10);
		Animation *attackAnima2 = this->createAttackAnimation("boy_attack_00_%02d.png", 4, 8, 15);
		this->setNormalAttackAction(Sequence::create(
			Animate::create(attackAnima1),
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction, this)),
			Animate::create(attackAnima2),
			Role::createIdleCallBackFunc(),
			NULL));

		Animation *gurtAnim = this->createNormalAnimation("boy_hurt_%02d.png", 2, 4);
		this->setHurtAction(Sequence::create(
			Animate::create(gurtAnim),
			Role::createIdleCallBackFunc(),
			NULL));

		Animation *deadAnim = this->createNormalAnimation("boy_dead_%02d.png", 3, 6);
		this->setDeadAction(Sequence::create(
			Animate::create(deadAnim),
			Blink::create(3, 9),
			NULL));

		ret = true;
		this->_bodyBox = this->createBoundingBox(Vec2(0, 30), Size(30, 60));
		this->_hitBox = this->createBoundingBox(Vec2(35, 50), Size(80, 90));
		ret = true;
	}while(0);
	return ret;
}

void Hero::onMove(Vec2 direction, float distance)
{
	this->setFlippedX(direction.x < 0 ? true : false);
	this->runWalkAction();
	Vec2 velocity=direction*(distance <33 ? 1 : 3);
	this->setVelocity(velocity);
}

void Hero::onStop()
{
	this->runIdleAction();
	this->setVelocity(Vec2::ZERO);
}

void Hero::onAttack()
{
	this->runNormalAttackAction();
}

void Hero::updateSelf()
{
	if (this->getCurrActionState() == ACTION_STATE_WALK)
	{
		Vec2 currentP = this->getPosition();				
		Vec2 expectP = currentP + this->getVelocity();	
		Vec2 actualP = expectP;			

		//limit the hero in the ground
		float mapWidth = global->tileMap->getContentSize().width;	
		float herofat = this->getBodyBox().actual.size.width / 2;																															
		float maptileHeight = global->tileMap->getTileSize().height;
		if (expectP.y < 0 || expectP.y > maptileHeight * 3)
		{
			actualP.y = currentP.y;
		}
		if (expectP.x < herofat || expectP.x >= mapWidth - herofat)
		{
			actualP.x = currentP.x;
		}
		this->setPosition(actualP);
		this->setLocalZOrder(Director::getInstance()->getVisibleSize().height - this->getPositionY());
	}
}

void Hero::attackCallBackAction(Ref* pSender)
{

}