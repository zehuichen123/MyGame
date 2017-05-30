#include "SkillButton.h"
SkillButton::SkillButton() :
	_itemSkillButton(NULL),
	_Mask(NULL),
	_ProgressTimer(NULL),
	CdTime(1.0f)
{}
SkillButton::~SkillButton()
{
}

SkillButton* SkillButton::create(const char* Normal, const char* Click,
	const char* Mask, float CDTime)
{
	SkillButton* skillButton = new SkillButton();
	if (skillButton&&skillButton->init(Normal, Click, Mask, CDTime))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		CC_SAFE_DELETE(skillButton);
		return nullptr;
	}
}

bool SkillButton::init(const char* Normal,const char* Click,
	const char* Mask,float CDTime)
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Node::init());
		_itemSkillButton = MenuItemImage::create(Normal, Click, CC_CALLBACK_1(SkillButton::ClickCallBack, this));
		_itemSkillButton->setPosition(Vec2::ZERO);

		auto MenuSkill = Menu::create(_itemSkillButton, NULL);
		MenuSkill->setPosition(Vec2::ZERO);
		addChild(MenuSkill, -100);

		_Mask = Sprite::create(Mask);
		_Mask->setPosition(Vec2::ZERO);
		_Mask->setVisible(false);
		addChild(_Mask, 0);

		_ProgressTimer = ProgressTimer::create(Sprite::create(Normal));
		_ProgressTimer->setType(ProgressTimer::Type::RADIAL);
		_ProgressTimer->setPosition(Vec2::ZERO);
		_ProgressTimer->setVisible(false);
		addChild(_ProgressTimer, 100);

		ret = true;
	} while (0);
	return ret;
}

void SkillButton::ClickCallBack(Ref* obj)
{
	_itemSkillButton->setEnabled(false);
	_Mask->setVisible(true);
	_ProgressTimer->setVisible(true);
	this->schedule(schedule_selector(SkillButton::CoolDownReduce), 0.1f);

	global->hero->runSkillAction();
	ActionInterval* action_progress_to = Sequence::create(
		ProgressTo::create(this->getCDTime(), 100),
		NULL);
	CallFunc* action_callback = CallFuncN::create(CC_CALLBACK_1(SkillButton::CoolDownCallBack, this));
	_ProgressTimer->runAction(Sequence::create(action_progress_to, action_callback, NULL));

}

void SkillButton::CoolDownReduce(float dt)
{
}

void SkillButton::CoolDownCallBack(Node* node)
{
	_itemSkillButton->setEnabled(true);

	_Mask->setVisible(false);

	_ProgressTimer->setVisible(false);
	_ProgressTimer->setPercentage(0);

	CdTime = this->getCDTime();

	this->unschedule(schedule_selector(SkillButton::CoolDownReduce));
}