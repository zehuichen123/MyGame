#include "skillButtonLayer.h"

skillButtonLayer::skillButtonLayer():type(0)
{}
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
	matrix = global->Gmatrix;		//get the matrix(Sprite pic) from the Global

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(skillButtonLayer::onTouchBegan, this);

	//you can move the matrix to determine where to release the skill
	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		matrix->setVisible(true);
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

	//judge if some enemies are attacked
	detected(_enemy);
}

void skillButtonLayer::detected(__Array* _enemy)
{
	auto matrixRect = matrix->getBoundingBox();
	auto toDeleteEnemy = __Array::create();
	toDeleteEnemy->retain();		//reference count++,or will be recycled

	for (int i = 0;i < _enemy->count();i++)
	{
		auto enemy = (Enemy*)_enemy->objectAtIndex(i);
		auto enemyRect = enemy->getBoundingBox();
		if (enemyRect.intersectsRect(matrixRect))
		{
			if (!enemy->beSkillAttack())
			{
				toDeleteEnemy->addObject(enemy);		//if this enemy's life value<0,add it to the toDeleteEnemy
			}
		}
	}

	//delete the dead enemy from the _enemy(Array)
	for (int i = 0;i < toDeleteEnemy->count();i++)
	{
		auto enemyToDelete = toDeleteEnemy->getObjectAtIndex(i);
		_enemy->removeObject(enemyToDelete);
	}
	toDeleteEnemy->removeAllObjects();
}

bool skillButtonLayer::onTouchBegan(Touch* touch, Event* event)
{
	auto touchPos = touch->getLocation();
	auto Button1Rect = Rect(
		cdButtonOne->getPosition().x - 40,
		cdButtonOne->getPosition().y - 40,
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

	//if you touch the button & cd is available & the magic value is enough 
	if (Button1Rect.containsPoint(touchPos)
		&& cdButtonOne->getAvail() == true
		&& global->GcityBloodSprite->magicCost(cdButtonOne->getCost()))
	{
		this->type = 1;
		return true;
	}
	else if (Button2Rect.containsPoint(touchPos)
		&& cdButtonTwo->getAvail() == true
		&& global->GcityBloodSprite->magicCost(cdButtonOne->getCost()))
	{
		this->type = 2;
		return true;
	}
	else if (Button3Rect.containsPoint(touchPos)
		&& cdButtonThree->getAvail() == true
		&& global->GcityBloodSprite->magicCost(cdButtonOne->getCost()))
	{
		this->type = 3;
		return true;
	}
	return false;
}