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

		matrix = Sprite::create("Game/MagicMatrix.png");
		matrix->setVisible(false);
		matrix->setPosition(visibleSize.width / 6 * 8, visibleSize.height / 15);
		this->addChild(matrix);

		cdButtonOne = magicSkillButton::create("abc");
		cdButtonTwo = magicSkillButton::create("abg");
		cdButtonThree = magicSkillButton::create("fd");
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
		if(Button1Rect.containsPoint(touchPos))
		{
			CCLOG("fjdsljf");
			this->type = 1;
			return true;
		}
		else if (Button2Rect.containsPoint(touchPos))
		{
			this->type = 2;
			return true;
		}
		else if (Button3Rect.containsPoint(touchPos))
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
		}
	}
	matrix->setVisible(false);
		
}