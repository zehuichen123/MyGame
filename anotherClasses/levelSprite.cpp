#include "levelSprite.h"
levelSprite::levelSprite()
{}
levelSprite::~levelSprite()
{}
levelSprite* levelSprite::createNum()
{
	auto LevelSprite = new levelSprite();
	//LevelSprite->initWithSpriteFrameName(picName);
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
void levelSprite::setLevelNum(int num)
{
	auto number = (LabelAtlas*)this->getChildByTag(2);
	char* temp = new char[12];
	sprintf(temp, "%d", num);
	number->setString(temp);
	log(temp);
	delete temp;
}
bool levelSprite::setUpdateView()
{
	bool ret = false;
	do {
		auto backGround = Sprite::create("game/stage_title.png");
		//backGround->setAnchorPoint(Point(1, 1));
		backGround->setPosition(Point::ZERO);
		this->addChild(backGround,0);

		auto number = LabelAtlas::create("0", "game/number_ttf.png", 72, 68, '0');
		number->setAnchorPoint(Point(0, 0.4));
		number->setPosition(this->getContentSize() / 2);
		//number->setPosition(Point(this->getContentSize()*3.4, this->getContentSize() / 2));
		this->addChild(number, 2, 2);
		//number->setScaleY(0);

		ret = true;
	} while (0);
	return ret;
}
void levelSprite::runLevelShowAnimation()
{
	this->stopAllActions();
	auto actionOne = ScaleTo::create(2, 1, 1);
	auto actionTwo = ScaleTo::create(2, 1, 0);
	this->runAction(Sequence::create(
		actionOne,
		actionTwo,
		CallFuncN::create(CC_CALLBACK_1(levelSprite::levelShowCallBack, this)),NULL));
}

void levelSprite::levelShowCallBack(Node* pSender)
{
	this->setScaleY(0);
}