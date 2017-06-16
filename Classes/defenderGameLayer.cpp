#include "defenderGameLayer.h"
#include <cmath>
#define PI 3.1415926
Scene* defenderGameLayer::createScene()
{
	Scene* scene = Scene::create();
	global->Gscene = scene;
	auto skillButton = skillButtonLayer::create();
	defenderGameLayer* layer = defenderGameLayer::create();
	global->GdefenderGameLayer = layer;
	scene->addChild(layer);
	scene->addChild(skillButton);
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

		bulletSample = Sprite::create("game/bullet.png");
		bulletSample->setAnchorPoint(Point(0, 0.5));
		bulletSample->setPosition(weapon->getPosition());
		this->addChild(bulletSample);

		auto pause = MenuItemSprite::create(
			Sprite::create("gmme/pause_button.png"),
			Sprite::create("gmme/pause_button.png"),
			CC_CALLBACK_1(defenderGameLayer::pauseCallBack, this));
		pause->setAnchorPoint(Point(0, 1));
		pause->setPosition(20, getWinSize().height - 20);

		auto matrix = Sprite::create("game/MagicMatrix.png");
		matrix->setVisible(false);
		matrix->setPosition(visibleSize.width / 6 * 8, visibleSize.height / 15);
		this->addChild(matrix);
		global->Gmatrix = matrix;

		auto bloodBg = Sprite::create("game/panelblood.png");
		bloodBg->setAnchorPoint(Point(0, 0));
		bloodBg->setPosition(Point::ZERO);
		bloodBg->setScale(1.3);
		this->addChild(bloodBg,5);

		auto blood = cityBloodSprite::create();
		
		blood->setPosition(Point::ZERO);
		//blood->setScale(1.3);
		bloodBg->addChild(blood);
		//bloodBg->scheduleUpdate();
		global->GcityBloodSprite = blood;
		
		auto SnailBar = snailBar::createPic();
		SnailBar->setAnchorPoint(Point(1, 0.5));
		SnailBar->setPosition(this->getWinSize().width -250, this->getWinSize().height - 40);
		SnailBar->setScale(1.5);
		this->addChild(SnailBar, 3, 6);
		SnailBar->runSnailAnimation();

		auto LevelSprite = levelSprite::createNum();
		LevelSprite->setPosition(getWinCenter());
		this->addChild(LevelSprite, 2, 7);
		LevelSprite->setScaleY(0);
		LevelSprite->setLevelNum(UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1));
		LevelSprite->runLevelShowAnimation();

		auto gameTipsSprite = GameTipsSprite::create();
		global->GgameTipsSprite = gameTipsSprite;
		CC_BREAK_IF(!gameTipsSprite);
		gameTipsSprite->setPosition(Point(90, getWinSize().height - 40));
		gameTipsSprite->setgoldNum(CCUserDefault::sharedUserDefault()->getIntegerForKey("goldNum", 0));
		gameTipsSprite->setMonstNum(1);
		gameTipsSprite->setMonstTotalNum(1);
		//gameTipsSprite->setMonstTotalNum(this->monsterBatch);
		gameTipsSprite->setStageNum(CCUserDefault::sharedUserDefault()->getIntegerForKey("lve", 1));
		this->addChild(gameTipsSprite, 3, 8);

		auto _Menu = Menu::create(pause, NULL);
		//CC_BREAK_IF(!_Menu);
		_Menu->setPosition(Point::ZERO);
		this->addChild(_Menu);

		

		schedule(schedule_selector(defenderGameLayer::updateCustom), 0.4f, kRepeatForever, 0);
		this->schedule(schedule_selector(defenderGameLayer::addEnemy), 1.0f);

		_bullet = __Array::create();
		_bullet->retain();
		_enemy = __Array::create();
		_enemy->retain();
		global->Genemy = _enemy;
		//_Array* toDeleteEnemy;
		toDeleteEnemy = __Array::create();
		toDeleteEnemy->retain();
		//__Array* toDeleteBullet;
		toDeleteBullet = __Array::create();
		toDeleteBullet->retain();

		this->scheduleUpdate();
		ret = true;
	} while (0);
	return ret;
}

void defenderGameLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto rota = this->getRotaSize(touch);

	auto touchPoint = touch->getLocation();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bullet = Sprite::create("game/bullet.png");
	_bullet->addObject(bullet);
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
	//this->removeChild(bullet);
	_bullet->removeObject(bullet);
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

void defenderGameLayer::addEnemy(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto target = Enemy::create();
	target->Enemy::Move();
	_enemy->addObject(target);
	//target->setPosition(getWinCenter());
	this->addChild(target);

}

void defenderGameLayer::update(float dt)
{
	for (int i = 0; i < _bullet->count(); i++)
	{
		bool flag = true;
		auto bullet = (Sprite*)_bullet->objectAtIndex(i);
		auto bulletRect = bullet->getBoundingBox();
		for (int j = 0; j < _enemy->count(); j++)
		{
			auto enemy = (Enemy*)_enemy->objectAtIndex(j);
			auto enemyRect = enemy->getBoundingBox();
			if (bulletRect.intersectsRect(enemyRect))
			{
				bool live = enemy->Enemy::beAttacked();
				if (!live)
				{
					toDeleteEnemy->addObject(enemy);
				}
				if (flag)
				{
					toDeleteBullet->addObject(bullet);
					flag = false;
				}
			}
			
		}
		for (int p = 0; p < toDeleteEnemy->count(); p++)
		{
			auto EnemyToDelete = toDeleteEnemy->objectAtIndex(p);
			_enemy->removeObject(EnemyToDelete);
			//this->removeChild((Node*)EnemyToDelete);
		}
		toDeleteEnemy->removeAllObjects();
	}
	for (int p = 0; p<toDeleteBullet->count(); p++)
	{
		auto BulletToDelete = toDeleteBullet->objectAtIndex(p);
		_bullet->removeObject(BulletToDelete);
		this->removeChild((Node*)BulletToDelete);
	}
	toDeleteBullet->removeAllObjects();
}

void defenderGameLayer::pauseCallBack(Ref* pSender)
{
	auto pauseLayer = GamePause::create();
	pauseLayer->setAnchorPoint(Point(0.5, 0.5));
	//pauseLayer->setPosition(getWinCenter());
	this->addChild(PopupLayer::create(pauseLayer),4);
}