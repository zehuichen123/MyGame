#include "levelSprite.h"
levelSprite::levelSprite()
{
	CCLOG("LevelSpriteOn");
}
levelSprite::~levelSprite()
{
	CCLOG("LevelSpriteOff");
}

levelSprite* levelSprite::createNum()
{
	auto LevelSprite = new levelSprite();
	if (LevelSprite&&LevelSprite->setUpdateView())
	{
		LevelSprite->autorelease();
		return LevelSprite;
	}
	else
	{
		CC_SAFE_DELETE(LevelSprite);
		return NULL;
	}
}


bool levelSprite::setUpdateView()
{
	bool ret = false;
	do {
		auto backGround = Sprite::create("game/stage_title.png");
		backGround->setPosition(Point::ZERO);
		this->addChild(backGround,0);

		auto number = LabelAtlas::create("0", "game/number_ttf.png", 54.6, 50, '0');
		number->setAnchorPoint(Point(0, 0.4));
		number->setPosition(this->getContentSize() / 2);
		this->addChild(number, 2, 2);

		ret = true;
	} while (0);
	return ret;
}

void levelSprite::setLevelNum(int num)
{
	auto number = (LabelAtlas*)this->getChildByTag(2);
	char* temp = new char[12];
	sprintf(temp, "%d", num);
	number->setString(temp);				//change the number of the level showing to player
	delete temp;
}
void levelSprite::runLevelShowAnimation()
{
	this->stopAllActions();
	auto actionOne = ScaleTo::create(2, 1, 1);			//scaleY from 0 to 1
	auto actionTwo = ScaleTo::create(2, 1, 0);			//scaleY from 1 to 0
	this->runAction(Sequence::create(
		actionOne,
		actionTwo,
		CallFuncN::create(CC_CALLBACK_1(levelSprite::levelShowCallBack, this)),NULL));
}

void levelSprite::levelShowCallBack(Node* pSender)
{
	this->setScaleY(0);
}
