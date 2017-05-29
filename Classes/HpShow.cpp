#include "HpShow.h"
HpShow::HpShow()
{
}
HpShow::~HpShow()
{
}

bool HpShow::init()
{
	bool ret = false;
	do {
		auto VisibleSize = Director::getInstance()->getVisibleSize();

		auto bloodBg = Sprite::create("bloodBg.png");
		bloodBg->setPosition(bloodBg->getContentSize().width / 2,
			VisibleSize.height - bloodBg->getContentSize().height / 2);
		this->addChild(bloodBg);

		_real = ProgressTimer::create(Sprite::create("blood.png"));
		_real->setType(ProgressTimer::Type::BAR);
		_real->setMidpoint(Point(0, 0.5));
		_real->setBarChangeRate(Point(1.0, 0));
		_real->setPosition(bloodBg->getContentSize() / 2);
		_real->setPercentage(100);
		bloodBg->addChild(_real);

		this->scheduleUpdate();
		ret = true;
	} while (0);
	return ret;
}

void HpShow::update(float dt)
{
	_real->setPercentage((float)global->hero->getcurLifeValue() / global->hero->getLifeValue() * 100);
}