#include "magicSkillButton.h"
magicSkillButton::magicSkillButton():
	avail(true),
	cost(10)
{
}
magicSkillButton::~magicSkillButton()
{
}
magicSkillButton* magicSkillButton::create(char* Icon)
{
	auto skillButton = new magicSkillButton();
	if (skillButton&&skillButton->setUpdateView(Icon))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else 
	{
		CC_SAFE_DELETE(skillButton);
		return NULL;
	}
}

bool magicSkillButton::setUpdateView(char* Icon)
{
	bool ret = false;
	do {
		cdIcon=Sprite::create();
		cdIcon->initWithSpriteFrameName(Icon);
		cdIcon->setPosition(this->getContentSize() / 2);
		if (!this->avail)
		{
			cdIcon->setVisible(false);
		}
		this->addChild(cdIcon,10);

		cdBar = ProgressTimer::create(Sprite::create("game/cdSkillButton.png"));
		cdBar->setPercentage(0);
		//cdBar->setAnchorPoint(Point(0.5, 0.5));
		cdBar->setType(ProgressTimer::Type::RADIAL);
		//cdBar->setBarChangeRate(Point(1, 0));
		//cdBar->setMidpoint(Point(0, 0));
		cdBar->setPosition(this->getContentSize()/2);
		this->addChild(cdBar,2);

		auto cdBg = Sprite::create("game/cdBg.png");
		cdBg->setPosition(this->getContentSize() / 2);
		this->addChild(cdBg,1);
		this->runCDAnimation();

		ret = true;
	} while (0);
	return ret;
}
void magicSkillButton::runCDAnimation()
{
	if (this->avail)
	{
		this->setAvail(false);
		cdIcon->setVisible(false);
		auto cdAction = ProgressTo::create(8, 100);
		auto actualAction=Sequence::create(
			cdAction, CallFuncN::create(CC_CALLBACK_1(magicSkillButton::cdCallBack, this)),NULL);
		cdBar->runAction(actualAction);
	}
}

void magicSkillButton::cdCallBack(Node* pSender)
{
	this->avail = true;
	cdIcon->setVisible(true);
}

void magicSkillButton::runSkillAnimationA(Layer* layer,Point point)
{
	if(this->avail)
	{ 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("specia/diyu.plist", "specia/diyu.png");
	auto monst = Sprite::create();
	monst->initWithSpriteFrameName("diyu0.png");
	Animation *yellowAnim = Role::createNormalAnimation("diyu%d.png", 15, 8);

	//CCAnimation *animation = CCAnimation::createWithSpriteFrames(sperci, 0.15f);
	CCAnimate *animate = CCAnimate::create(yellowAnim);
	CCSequence* pse = CCSequence::create(animate,CallFuncN::create(CC_CALLBACK_1(magicSkillButton::skillCallBack,this)), NULL);
	monst->setAnchorPoint(this->getAnchorPoint());
	monst->setPosition(point - Point(200, 200));
	layer->addChild(monst, 3);

	//monst->runAction(CCRepeatForever::create(pse));

	//this->avail = false;//设为不可用
	this->cdBar->setPercentage(0);
	this->runCDAnimation();
	monst->runAction(pse);
	}
}
void magicSkillButton::runSkillAnimationB(Layer* layer,Point point)
{
	if (this->avail)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("specia/ligtht.plist", "specia/ligtht.png");
		auto monst = Sprite::create();
		monst->initWithSpriteFrameName("light0.png");
		Animation *purpleAnim = Role::createNormalAnimation("light%d.png", 17, 8);

		auto *animate = Animate::create(purpleAnim);
		CCSequence* pse = CCSequence::create(animate, CallFuncN::create(CC_CALLBACK_1(magicSkillButton::skillCallBack, this)), NULL);
		monst->setAnchorPoint(this->getAnchorPoint());
		monst->setPosition(point - Point(300, 300));
		layer->addChild(monst, 3);

		//monst->runAction(CCRepeatForever::create(pse));

		//this->avail = false;//设为不可用
		this->cdBar->setPercentage(0);
		this->runCDAnimation();
		monst->runAction(pse);
	}
}
void magicSkillButton::runSkillAnimationC(Layer* layer,Point point)
{
	if (this->avail)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("specia/long.plist", "specia/long.png");
		auto monst = Sprite::create();
		monst->initWithSpriteFrameName("long0.png");
		Animation *blueAnim = Role::createNormalAnimation("long%d.png", 14, 8);

		auto animate = Animate::create(blueAnim);
		auto pse = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_1(magicSkillButton::skillCallBack, this)), NULL);
		monst->setAnchorPoint(this->getAnchorPoint());
		monst->setPosition(point - Point(200, 200));
		layer->addChild(monst, 3);

		this->detected(point);
		//this->avail = false;
		this->cdBar->setPercentage(0);
		this->runCDAnimation();
		monst->runAction(pse);
	}
}

void magicSkillButton::detected(Point point)
{
	
}

void magicSkillButton::skillCallBack(Node* pSender)
{
	auto monst = (Sprite*)pSender;
	auto de = (Layer*)monst->getParent();
	de->removeChild(pSender, true);

}



