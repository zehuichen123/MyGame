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

		auto map = MapLayer::create();
		this->addChild(map, -100);
		this->scheduleUpdate();

		ret = true;
	} while (0);
	return ret;
}
void GameLayer::update(float dt)
{
	this->updateHero(dt);
}
void GameLayer::updateHero(float dt)
{
	m_pHero->updateSelf();//自更新状态
}
void GameLayer::addHero()
{
	m_pHero = Hero::create();
	m_pHero->setPosition(_visibleOrigin + Vec2(100, 50));
	m_pHero->runIdleAction();
	//属性设置
	m_pHero->setDamageStrength(15);
	m_pHero->setLifeValue(200);
	m_pHero->setcurLifeValue(m_pHero->getLifeValue());

	m_pHero->setLocalZOrder(_visibleSize.height - m_pHero->getPositionY());
	this->addChild(m_pHero);
}