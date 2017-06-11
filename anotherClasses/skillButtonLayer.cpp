#include "skillButtonLayer.h"
skillButtonLayer::skillButtonLayer()
{
	this->type = 0;
}
skillButtonLayer::~skillButtonLayer()
{}
bool skillButtonLayer::init()
{
	bool ret = false;
	do {

		auto visibleSize = Director::getInstance()->getVisibleSize();

		CC_BREAK_IF(!Layer::init());
		

		cdButtonOne = magicSkillButton::create("diyus.png");
		cdButtonTwo = magicSkillButton::create("lights.png");
		cdButtonThree = magicSkillButton::create("longs.png");
		cdButtonOne->setPosition(visibleSize.width * 7/8, visibleSize.height/13 );
		cdButtonTwo->setPosition(visibleSize.width * 6/8, visibleSize.height / 13);
		cdButtonThree->setPosition(visibleSize.width * 5/8, visibleSize.height / 13);
		this->addChild(cdButtonOne);
		this->addChild(cdButtonTwo);
		this->addChild(cdButtonThree);


		ret = true;
	} while (0);
	return ret;
}
void skillButtonLayer::onEnter()
{
	Layer::onEnter();
	matrix = global->Gmatrix;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		auto touchPos = touch->getLocation();
		auto Button1Rect = Rect(
			cdButtonOne->getPosition().x-40,
			cdButtonOne->getPosition().y-40,
			80, 80);
		auto Button2Rect = Rect{
			cdButtonTwo->getPosition().x - 40,
			cdButtonTwo->getPosition().y - 40,
			80, 80
		};
		auto Button3Rect = Rect{
			cdButtonThree->getPosition().x - 40,
			cdButtonThree->getPosition().y - 40,
			80, 80
		};
		if(Button1Rect.containsPoint(touchPos)
			&&cdButtonOne->getAvail()==true
			&&global->GcityBloodSprite->magicCost(cdButtonOne->getCost()))
		{
			this->type = 1;
			return true;
		}
		else if (Button2Rect.containsPoint(touchPos)
			&&cdButtonTwo->getAvail()==true
			&& global->GcityBloodSprite->magicCost(cdButtonOne->getCost()))
		{
			this->type = 2;
			return true;
		}
		else if (Button3Rect.containsPoint(touchPos)
			&&cdButtonThree->getAvail()==true
			&& global->GcityBloodSprite->magicCost(cdButtonOne->getCost()))
		{
			this->type = 3;
			return true;
		}
		return false;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		
		CCLOG("fdslkfjlf");
		matrix->setVisible(true);
		//auto action = MoveTo::create(0.05f, touch->getLocation());
		//matrix->runAction(action);
		matrix->setPosition(touch->getLocation());
	};

	if (this->type==0)
	{
		listener->setSwallowTouches(true);
	}
	listener->onTouchEnded = CC_CALLBACK_2(skillButtonLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
}

void skillButtonLayer::onTouchEnded(Touch* touch, Event* event)
{
	//auto action = MoveTo::create(0.05f, touch->getLocation());
	//matrix->runAction(action);
	auto _enemy = global->Genemy;
	matrix->setPosition(touch->getLocation());
	switch (this->getType())
	{
		case 1:
		{
			cdButtonOne->runSkillAnimationA(this, touch->getLocation());
			break;
		}
		case 2:
		{
			cdButtonTwo->runSkillAnimationB(this, touch->getLocation());
			break;
		}
		case 3:
		{
			cdButtonThree->runSkillAnimationC(this, touch->getLocation());
			break;
		}
	}
	matrix->setVisible(false);
	detected(_enemy);
}

void skillButtonLayer::detected(__Array* _enemy)
{
	auto matrixRect = matrix->getBoundingBox();
	auto toDeleteEnemy = __Array::create();
	toDeleteEnemy->retain();
	for (int i = 0;i < _enemy->count();i++)
	{
		auto enemy = (Enemy*)_enemy->objectAtIndex(i);
		auto enemyRect = enemy->getBoundingBox();
		if (enemyRect.intersectsRect(matrixRect))
		{
			enemy->beSkillAttack();
			toDeleteEnemy->addObject(enemy);
		}
	}
	for (int i = 0;i < toDeleteEnemy->count();i++)
	{
		auto enemyToDelete = toDeleteEnemy->getObjectAtIndex(i);
		_enemy->removeObject(enemyToDelete);
	}
	toDeleteEnemy->removeAllObjects();
}