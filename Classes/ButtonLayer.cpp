#include "ButtonLayer.h"
#include "Global.h"
ButtonLayer::ButtonLayer()
{
}
ButtonLayer::~ButtonLayer()
{
}
bool ButtonLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		auto visibleSize = Director::getInstance()->getVisibleSize();
		//add buttons in four directions
		MoveLeft = Sprite::create("Button.png");
		MoveRight = Sprite::create("Button.png");
		MoveDown = Sprite::create("Button.png");
		MoveUp = Sprite::create("Button.png");

		MoveLeft->setScale(0.5);
		MoveLeft->setPosition(Point(visibleSize.width * 23 / 100, visibleSize.height * 20 / 100));
		this->addChild(MoveLeft);

		MoveRight->setScale(0.5);
		MoveRight->setFlippedX(true);
		MoveRight->setPosition(Point(visibleSize.width * 8 / 100, visibleSize.height * 20 / 100));
		this->addChild(MoveRight);

		MoveDown->setScale(0.5);
		MoveDown->setRotation(90);
		MoveDown->setPosition(Point(visibleSize.width * 16 / 100, visibleSize.height * 8 / 100));
		this->addChild(MoveDown);
		
		MoveUp->setScale(0.5);
		MoveUp->setRotation(270);
		MoveUp->setPosition(Point(visibleSize.width * 16 / 100, visibleSize.height * 32 / 100));
		this->addChild(MoveUp);

		//add touch event to the button
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(ButtonLayer::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(ButtonLayer::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(ButtonLayer::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ret = true;
	} while (0);
	return ret;
}
bool ButtonLayer::onTouchBegan(Touch* touch, Event* event)
{
	auto pos = touch->getLocation();

	auto Left = Rect(
		MoveLeft->getPositionX() - MoveLeft->getContentSize().width / 2,
		MoveLeft->getPositionY() - MoveLeft->getContentSize().height / 2,
		MoveLeft->getContentSize().width,
		MoveLeft->getContentSize().height);

	auto Right = Rect(
		MoveRight->getPositionX() - MoveRight->getContentSize().width / 2,
		MoveRight->getPositionY() - MoveRight->getContentSize().height / 2,
		MoveRight->getContentSize().width,
		MoveRight->getContentSize().height);

	auto Up = Rect(
		MoveUp->getPositionX() - MoveUp->getContentSize().width / 2,
		MoveUp->getPositionY() - MoveUp->getContentSize().height / 2,
		MoveUp->getContentSize().width,
		MoveUp->getContentSize().height);

	auto Down = Rect(
		MoveDown->getPositionX() - MoveDown->getContentSize().width / 2,
		MoveDown->getPositionY() - MoveDown->getContentSize().height / 2,
		MoveDown->getContentSize().width,
		MoveDown->getContentSize().height);

	if (Left.containsPoint(pos))
	{
		Direction = Vec2(11, 0);
		updateHero(touch);
	}
	else if (Right.containsPoint(pos))
	{
		Direction = Vec2(-11, 0);
		updateHero(touch);
	}
	else if (Up.containsPoint(pos))
	{
		Direction = Vec2(0, 11);
		updateHero(touch);
	}
	else if(Down.containsPoint(pos))
	{
		Direction = Vec2(0, -11);
		updateHero(touch);
	}
	return true;

}

void ButtonLayer::onTouchEnded(Touch* touch, Event* event)
{
	global->hero->onStop();
	Direction = Vec2(0, 0);
}

void ButtonLayer::onTouchMoved(Touch* touch, Event* event)
{
	updateHero(touch);
}

void ButtonLayer::updateHero(Touch* touch)
{
	global->hero->onMove(Direction,1);
}