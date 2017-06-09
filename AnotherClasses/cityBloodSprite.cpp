#include "cityBloodSprite.h"
cityBloodSprite::cityBloodSprite():
	cityBlood(100),
	magicValue(100)
{
	CCLOG("cityBloodSpriteOn");
}
cityBloodSprite::~cityBloodSprite()
{
}
cityBloodSprite* cityBloodSprite::create()
{
	auto bloodSprite = new cityBloodSprite();
	if (bloodSprite&&bloodSprite->setUpdateView())
	{
		bloodSprite->autorelease();
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

		auto bloodBar = ProgressTimer::create(Sprite::create("game/cityBlood.png"));
		bloodBar->setAnchorPoint(Point(0, 0.5));
		bloodBar->setType(ProgressTimer::Type::BAR);
		bloodBar->setMidpoint(Point(0, 0));
		bloodBar->setBarChangeRate(Point(1, 0));
		bloodBar->setPercentage(100);
		bloodBar->setPosition(Point(53,26));
		this->addChild(bloodBar);

		auto magicBar = ProgressTimer::create(Sprite::create("game/magic.png"));
		magicBar->setAnchorPoint(Point(0, 0.5));
		magicBar->setType(ProgressTimer::Type::BAR);
		magicBar->setMidpoint(Point(0, 0));
		magicBar->setBarChangeRate(Point(1, 0));
		magicBar->setPosition(Point(51, 15));
		magicBar->setPercentage(100);
		this->addChild(magicBar);

		ret = true;
	} while (0);
	return ret;
}