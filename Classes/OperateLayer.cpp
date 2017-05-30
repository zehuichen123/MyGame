#include "OperateLayer.h"

OperateLayer::OperateLayer() {
	//auto global = Global::instance();
	global->operateLayer = this;
}
OperateLayer::~OperateLayer() {}
bool OperateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		//code
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto WinSize = Director::getInstance()->getWinSize();
		//add a attack button
		auto attackItem = MenuItemImage::create("attackbuttonNormal.png", "attackbuttonSelected.png",
			CC_CALLBACK_1(OperateLayer::attackButton, this));
		attackItem->setScale(1.5);
		attackItem->setPosition(visibleSize.width - attackItem->getContentSize().width / 2 - 50,
			attackItem->getContentSize().height / 2 + 20);

		auto menu = Menu::create(attackItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 100);

		auto skillA = SkillButton::create("SkillButton.png", 3.0f);
		skillA->setPosition(attackItem->getPosition() - Vec2(50, 0));
		this->addChild(skillA);

		
		auto pause = Button::create("pause.png");
		pause->setPosition(WinSize - pause->getContentSize()/2);
		pause->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				addChild(PopupLayer::create(GamePause::create()));
				Director::getInstance()->pause();
			}
			break;
			}
		});
		addChild(pause);
		ret = true;
	} while (0);
	return ret;
}

void OperateLayer::attackButton(Ref* psender)
{
	global->hero->onAttack();
}