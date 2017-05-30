#include "GameLayer.h"

GameLayer::GameLayer()
{
	global->gameLayer = this;
}
GameLayer::~GameLayer()
{
}
bool GameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		_visibleSize = Director::getInstance()->getVisibleSize();
		_visibleOrigin = Director::getInstance()->getVisibleOrigin();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boy.plist", "Boy.pvr.ccz");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy.plist", "Enemy.pvr.ccz");

		this->addHero();
		this->addEnemis(5);

		auto map = MapLayer::create();
		this->addChild(map, -100);
		this->scheduleUpdate();
		global->enemies = m_pEnemies;
		ret = true;
	} while (0);
	return ret;
}
void GameLayer::update(float dt)
{
	this->updateEnemies(dt);
	this->updateHero(dt);
}
void GameLayer::updateHero(float dt)
{
	m_pHero->updateSelf();
}
void GameLayer::addHero()
{
	m_pHero = Hero::create();
	m_pHero->setPosition(_visibleOrigin + Vec2(100, 50));
	m_pHero->runIdleAction();

	//set characters of the hero
	m_pHero->setDamageStrength(15);
	m_pHero->setLifeValue(200);
	m_pHero->setcurLifeValue(m_pHero->getLifeValue());

	m_pHero->setLocalZOrder(_visibleSize.height - m_pHero->getPositionY());
	this->addChild(m_pHero);
}

void GameLayer::updateEnemies(float dt)
{
	Ref* Obj = NULL;
	//Vec2 distance = Vec2::ZERO;
	CCARRAY_FOREACH(m_pEnemies, Obj)
	{
		Enemy* pEnemy = (Enemy*) Obj;
		pEnemy->updateSelf();

		if (pEnemy->getDeadAction()->isDone())
		{
			m_pEnemies->removeObject(pEnemy);
		}
	}
}

void GameLayer::addEnemis(int num)
{
	m_pEnemies = __Array::createWithCapacity(num);
	m_pEnemies->retain();   //what's this????
	for (int i = 0; i < num; i++)
	{
		Enemy *pEnemy = Enemy::create();
		pEnemy->setPosition(Vec2(random(_visibleSize.width / 2, _visibleSize.width), 70));
		pEnemy->runIdleAction();
		pEnemy->setLocalZOrder(_visibleSize.height - pEnemy->getPositionY());

		pEnemy->setVelocity(Vec2(0.5f, 0.5f));
		pEnemy->setEyeArea(300);
		pEnemy->setAttackArea(80);
		pEnemy->setDamageStrength(5);
		pEnemy->setLifeValue(100);
		pEnemy->setcurLifeValue(m_pHero->getLifeValue());

		m_pEnemies->addObject(pEnemy);
		this->addChild(pEnemy, 0);
	}
}