#include "cityBloodSprite.h"
cityBloodSprite::cityBloodSprite():
	cityBlood(100),
	magicValue(100)
{
	CCLOG("cityBloodSpriteOn");
}
cityBloodSprite::~cityBloodSprite()
{}
cityBloodSprite* cityBloodSprite::create()
{
	auto bloodSprite = new cityBloodSprite();
	if (bloodSprite&&bloodSprite->setUpdateView())
	{
		bloodSprite->autorelease();
		//global->GcityBloodSprite = bloodSprite;
		return bloodSprite;
	}
	else
	{
		CC_SAFE_DELETE(bloodSprite);
		return NULL;
	}
}
bool cityBloodSprite::setUpdateView()
{
	bool ret = false;
	do {

		bloodBar = ProgressTimer::create(Sprite::create("game/cityBlood.png"));
		bloodBar->setAnchorPoint(Point(0, 0.5));
		bloodBar->setType(ProgressTimer::Type::BAR);
		bloodBar->setMidpoint(Point(0, 0));
		bloodBar->setBarChangeRate(Point(1, 0));
		bloodBar->setPercentage(100);
		bloodBar->setPosition(Point(67,33));
		this->addChild(bloodBar);

		magicBar = ProgressTimer::create(Sprite::create("game/magic.png"));
		magicBar->setAnchorPoint(Point(0, 0.5));
		magicBar->setType(ProgressTimer::Type::BAR);
		magicBar->setMidpoint(Point(0, 0));
		magicBar->setBarChangeRate(Point(1, 0));
		magicBar->setPosition(Point(62, 19));
		magicBar->setPercentage(100);
		this->addChild(magicBar);

		//recover your blue bar every 1s with 1 point
		this->schedule(schedule_selector(cityBloodSprite::recoverMagic), 1.0f);
		ret = true;
	} while (0);
	return ret;
}

void cityBloodSprite::beAttack(float hurt)
{
	auto currCityBlood = this->getCityBlood();
	if (currCityBlood - hurt > 0)
	{
		this->setCityBlood(currCityBlood - hurt);
		bloodBar->setPercentage(currCityBlood-hurt);
	}
	else {
		auto scene = gameOverLayer::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}
}

bool cityBloodSprite::magicCost(float value)
{
	auto currMagicValue = this->getMagicValue();
	if (currMagicValue - value > 0)		//the remained blue bar is enough for a skill use return true
	{
		this->setMagicValue(currMagicValue - value);
		magicBar->setPercentage(this->getMagicValue());
		return true;			
	}
	else								//can use the skill
	{
		return false;
	}
}

void cityBloodSprite::recoverMagic(float dt)
{
	auto value = global->GcityBloodSprite->getMagicValue();
	if (value < 100)
	{
		value += 1;
	}
	global->GcityBloodSprite->setMagicValue(value);
	global->GcityBloodSprite->magicBar->setPercentage(this->getMagicValue());
}
