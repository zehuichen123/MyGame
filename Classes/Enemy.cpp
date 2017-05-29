#include "Enemy.h"
Enemy::Enemy() :
	m_nextDecisionTime(0)
{}
Enemy::~Enemy()
{}

bool Enemy::init()
{
	bool ret = false;
	do {
		this->initWithSpriteFrameName("bear_idle_00.png");
		//this->setAnchorPoint(Vec2(0.25f, 0.15f));

		Animation *idleAnim = this->createNormalAnimation("bear_idle_%02d.png", 3, 6);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		Animation *walkAnim = this->createNormalAnimation("bear_run_%02d.png", 4, 8);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		Animation *attackAnim = this->createAttackAnimation("bear_attack_00_%02d.png", 0, 8, 8);
		this->setNormalAttackAction(Sequence::create(Animate::create(attackAnim),
			CallFuncN::create(CC_CALLBACK_1(Enemy::attackCallBackAction, this)),
			Role::createIdleCallBackFunc(),
			NULL));

		Animation *hurtAnim = this->createNormalAnimation("bear_hurt_%02d.png", 2, 4);
		this->setHurtAction(Sequence::create(Animate::create(hurtAnim), Role::createIdleCallBackFunc(), NULL));

		Animation *deadAnim = this->createNormalAnimation("bear_dead_%02d.png", 2, 4);
		this->setDeadAction(Sequence::create(Animate::create(deadAnim), Blink::create(3, 9), NULL));

		Size enemyShowSize = this->getSpriteFrame()->getRect().size;
		this->_bodyBox = this->createBoundingBox(Vec2(0, 35), Size(60, 70));
		this->_hitBox = this->createBoundingBox(Vec2(40, 35), Size(80, 70));


		ret = true;
	} while (0);

	return ret;
}
void Enemy::updateSelf()
{
	this->execute(global->hero->getPosition(), global->hero->getBodyBox().actual.size.width);
	if (this->getCurrActionState() == ACTION_STATE_WALK)
	{
		Vec2 location = this->getPosition();
		Vec2 direction = this->getMoveDirection();
		Vec2 expectP = location + direction;
		float maptileHeight = global->tileMap->getTileSize().height;
		//if(expectP.y<0 || !global->tileAllowMove(expectP))
		if (expectP.y < 0 || expectP.y > maptileHeight * 3)
		{
			direction.y = 0;
		}
		this->setFlippedX(direction.x < 0 ? true : false);
		this->setPosition(location + direction);
		this->updateBoxes();
		this->setLocalZOrder(this->getPositionY());
	}
	if (this->getCurrActionState() == ACTION_STATE_NORMAL_ATTACK)
	{
		this->runNormalAttackAction();
	}
}

/* avoid appearing some strange situations -don't judge soon */
void Enemy::execute(const Vec2& target, float targetBodyWidth)
{
	if (m_nextDecisionTime == 0)
	{
		this->decide(target, targetBodyWidth);
	}
	else {
		--m_nextDecisionTime;
	}
}

void Enemy::decide(const Vec2& target, float targetBodyWidth)
{
	Vec2 location = this->getPosition();
	float distance = location.getDistance(target);
	distance = distance - targetBodyWidth / 2;

	bool isFlippedX = this->isFlippedX();
	bool isOnTargetLeft = (location.x < target.x ? true : false);
	if ((isFlippedX && isOnTargetLeft) || (!isFlippedX && !isOnTargetLeft)) {
		this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
	}
	else {
		if (distance < m_eyeArea)
		{
			this->m_aiState = (distance < m_attackArea) && ((fabsf(location.y - target.y) < 15)) ? AI_ATTACK : AI_PURSUE;
		}
		else {
			this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
		}
	}
	switch (m_aiState)
	{
	case AI_ATTACK:
	{
		this->runNormalAttackAction();
		this->m_nextDecisionTime = 50;
	}
	break;
	case AI_IDLE:
	{
		this->runIdleAction();
		this->m_nextDecisionTime = CCRANDOM_0_1() * 100;
	}
	break;
	case AI_PATROL:
	{
		this->runWalkAction();
		this->m_moveDirection.x = CCRANDOM_MINUS1_1();
		this->m_moveDirection.y = CCRANDOM_MINUS1_1();
		m_moveDirection.x = m_moveDirection.x > 0 ? (m_moveDirection.x + velocity.x) : (m_moveDirection.x - velocity.x);
		m_moveDirection.y = m_moveDirection.y > 0 ? (m_moveDirection.y + velocity.y) : (m_moveDirection.y - velocity.y);
		this->m_nextDecisionTime = CCRANDOM_0_1() * 100;
	}
	break;
	case AI_PURSUE:
	{
		this->runWalkAction();
		this->m_moveDirection = (target - location).getNormalized();
		this->setFlippedX(m_moveDirection.x < 0 ? true : false);
		m_moveDirection.x = m_moveDirection.x > 0 ? (m_moveDirection.x + velocity.x) : (m_moveDirection.x - velocity.x);
		m_moveDirection.y = m_moveDirection.y > 0 ? (m_moveDirection.y + velocity.y) : (m_moveDirection.y - velocity.y);
		this->m_nextDecisionTime = 10;
	}
	break;
	}
}


void Enemy::attackCallBackAction(Node* pSender)
{
	Hero* t_hero = global->hero;
	Rect attackReck = _hitBox.actual;
	Rect hurtReck = t_hero->getBodyBox().actual;
	if (attackReck.intersectsRect(hurtReck))
	{
		t_hero->setAllowMove(false);
		int damage = this->getDamageStrength()*0.2f;
		t_hero->runHurtAction();
		t_hero->setcurLifeValue(t_hero->getcurLifeValue() - damage);
	}
	if (t_hero->getcurLifeValue() <= 0)
	{
		t_hero->runDeadAction();
		t_hero->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
	}
}