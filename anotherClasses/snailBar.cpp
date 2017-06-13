#include "snailBar.h"
snailBar::snailBar():
	runTime(10)
{}
snailBar::~snailBar()
{}
snailBar* snailBar::createPic()
{
	auto SnailBar = new snailBar();
	if (SnailBar&&SnailBar->setUpdateView())
	{
		SnailBar->autorelease();
		return SnailBar;
	}
	else
	{
		CC_SAFE_DELETE(SnailBar);
		return NULL;
	}
}
bool snailBar::setUpdateView()
{
	bool ret = false;
	do {
		snail = Sprite::create("game/snail.png");
		snail->setAnchorPoint(Point(0, 0.5));
		snail->setPosition(this->getContentSize().width+120, this->getContentSize().height / 2);
		this->addChild(snail,2);

		snailBg = Sprite::create("game/snailBg.png");
		snailBg->setPosition(this->getContentSize().width, this->getContentSize().height / 2);
		this->addChild(snailBg,0);

		SnailBar = ProgressTimer::create(Sprite::create("game/snailBar.png"));
		SnailBar->setPercentage(0);
		SnailBar->setType(ProgressTimer::Type::BAR);
		SnailBar->setBarChangeRate(Point(1, 0));
		SnailBar->setMidpoint(Point(1, 0));
		this->addChild(SnailBar,1);

		ret = true;
	} while (0);
	return ret;
}

void snailBar::runSnailAnimation()
{
	auto barMove= ProgressFromTo::create( this->getRunTime(),8, 100);
	//auto barMoveTwo=Sequence::create(barMove, CallFuncN::create(CC_CALLBACK_1(cityBloodSprite::gameCallBack, this)), NULL);
	auto snailMove = MoveTo::create(this->getRunTime(), Point(-200, this->getContentSize().height / 2));
	snail->runAction(snailMove);
	SnailBar->runAction(Sequence::create(barMove, CallFuncN::create(CC_CALLBACK_1(snailBar::gameCallBack, this)), NULL));
}

void snailBar::gameCallBack(Node* pSender)
{
	auto bln = global->GcityBloodSprite->getCityBlood();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("lifetemp", bln);
	auto scene = GameSuccessfullyLayer::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, scene));
}