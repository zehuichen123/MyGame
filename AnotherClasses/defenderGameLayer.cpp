#include "defenderGameLayer.h"
#include <cmath>
#define PI 3.1415926
Scene* defenderGameLayer::createScene()
{
	Scene* scene = Scene::create();
	defenderGameLayer* layer = defenderGameLayer::create();
	scene->addChild(layer);
	return scene;
}
void defenderGameLayer::onEnter()
{
	BaseLayer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		auto rota = this->getRotaSize(touch);
		auto weaponAction = RotateTo::create(0.2f, rota);
		auto bulletAction = RotateTo::create(0.2f, rota);
		auto moveAction = Spawn::create(weaponAction,bulletAction, NULL);
		weapon->runAction(weaponAction);
		bulletSample->runAction(bulletAction);
		return true;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		auto rota = this->getRotaSize(touch);
		auto weaponAction = RotateTo::create(0.2f, rota);
		auto bulletAction = RotateTo::create(0.2f, rota);
		auto moveAction = Spawn::create(weaponAction, bulletAction, NULL);
		weapon->runAction(weaponAction);
		bulletSample->runAction(bulletAction);
	};
	listener->onTouchEnded = CC_CALLBACK_2(defenderGameLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(defenderGameLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool defenderGameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		CC_BREAK_IF(!setUpdateView());
		schedule(schedule_selector(defenderGameLayer::updateCustom), 0.4f, kRepeatForever, 0);
		ret = true;
	} while (0);
	return ret;
}
bool defenderGameLayer::setUpdateView()
{
	bool ret = false;
	do {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

		auto backGround = Sprite::create("gmbg/gamebg.png");
		backGround->setScale(1.3);
		backGround->setPosition(getWinCenter());
		this->addChild(backGround);

		weapon = Sprite::create("game/weapon.png");
		weapon->setPosition(
			weapon->getContentSize().width / 2 + visibleOrigin.x,
			visibleOrigin.y + visibleSize.height / 2);
		this->addChild(weapon);

		bulletSample = Sprite::create("Game/bullet.png");
		bulletSample->setAnchorPoint(Point(0, 0.5));
		bulletSample->setPosition(weapon->getPosition());
		this->addChild(bulletSample);
		ret = true;
	} while (0);
	return ret;
}

void defenderGameLayer::onTouchCancelled(Touch* touch, Event* event)
{
}
void defenderGameLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto rota = this->getRotaSize(touch);

	auto touchPoint = touch->getLocation();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bullet = Sprite::create("Game/bullet.png");
	bullet->setAnchorPoint(Point(0, 0.5));
	bullet->setRotation(rota);
	bullet->setPosition(weapon->getPosition());
	
	int offX = touchPoint.x - bullet->getPosition().x;
	int offY = touchPoint.y - bullet->getPosition().y;

	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;

	// Ok to add now - we've double checked position
	this->addChild(bullet);

	// Determine where we wish to shoot the bullet to
	int realX = visibleSize.width + (bullet->getContentSize().width / 2);
	float ratio = (float)offY / (float)offX;
	int realY = (realX * ratio) + bullet->getPosition().y;
	auto realDest = Point(realX, realY);

	// Determine the length of how far we're shooting
	int offRealX = realX - bullet->getPosition().x;
	int offRealY = realY - bullet->getPosition().y;
	float length = sqrtf((offRealX*offRealX) + (offRealY*offRealY));
	float velocity = 960 / 1;   // 960pixels/1sec
	float realMoveDuration = length / velocity;

	// Move bullet to actual endpoint
	bullet->runAction(
		Sequence::create(MoveTo::create(realMoveDuration, realDest),
			CallFuncN::create(CC_CALLBACK_1(defenderGameLayer::bulletMoveFinished, this)),
			NULL));
	bulletSample->setVisible(false);
}

void defenderGameLayer::bulletMoveFinished(Ref* pSender)
{
	Sprite* bullet = (Sprite*)pSender;
	this->removeChild(bullet);
}

float defenderGameLayer::getRotaSize(Touch* touch)
{
	Point touchPos = touch->getLocation();
	Point weaponPos = weapon->getPosition();
	float chy = touchPos.y - weaponPos.y;
	float chx = touchPos.x - weaponPos.x;
	float hud = std::atan(chy / chx);

	float rota = -(hud*(180 / PI));
	return rota;
}
void defenderGameLayer::updateCustom(float dt)
{
	bulletSample->setVisible(true);
}