#include "button.h"
Button::Button()
{}
Button::~Button()
{}
bool Button::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		auto visibleSize = Director::getInstance()->getVisibleSize();
		//put the 4 buttons
		MoveLeft = Sprite::create("button.png");
		MoveRight = Sprite::create("button.png");
		MoveDown = Sprite::create("button.png");
		MoveUp = Sprite::create("button.png");
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

		//add touch event
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(Button::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ret = true;
	} while (0);
	return ret;
}
bool Button::onTouchBegan(Touch* touch, Event* event)
{
	//按下事件处理
	auto pos = touch->getLocation();
	auto Left = MoveLeft->getCenterRect();
	auto Right = MoveRight->getCenterRect();
	auto Up = MoveUp->getCenterRect();
	auto Down = MoveDown->getCenterRect();
	if (Left.containsPoint(pos))
	{
		Direction = Vec2(11, 0);
	}
	else if (Right.containsPoint(pos))
	{
		Direction = Vec2(-11, 0);
	}
	else if (Up.containsPoint(pos))
	{
		Direction = Vec2(0, 11);
	}
	else
	{
		Direction = Vec2(0, -11);
	}
	updateHero(touch);
	return true;
	
}
void Button::onTouchEnded(Touch* touch, Event* event)
{
}
void Button::onTouchMoved(Touch* touch, Event* event)
{	
	updateHero(touch);
}
void Button::updateHero(Touch* touch)
{
	global->hero->onMove(Direction, 33);
}