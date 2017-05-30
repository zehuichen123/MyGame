#include "GamePause.h"

GamePause::GamePause()
{
}
GamePause::~GamePause()
{
}
bool GamePause::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());

		Size WinSize = Director::getInstance()->getWinSize();
		Vec2 CenterPoint = Vec2(WinSize.width / 2,WinSize.height/2);

		auto continueButton = Button::create("buttonClick.png");
		continueButton->setTitleText("contitue");
		continueButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				getParent()->removeFromParent();
				Director::getInstance()->resume();
			}
			}
		});

		auto restartButton = Button::create("buttonClick.png");
		restartButton->setTitleText("Restart");
		restartButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				Director::getInstance()->resume();
				Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
			}
			}
		});

		auto toTitleButton = Button::create("buttonClick.png");
		toTitleButton->setTitleText("ToTitle");
		toTitleButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				Director::getInstance()->resume();
				//Director::getInstance()->replaceScene( GameStartScene::createScene());
			}
			}
		});
		continueButton->setPosition(CenterPoint + Vec2(0, 50));
		restartButton->setPosition(CenterPoint);
		toTitleButton->setPosition(CenterPoint + Vec2(0, -50));
		this->addChild(continueButton);
		this->addChild(restartButton);
		this->addChild(toTitleButton);
		ret = true;
	} while (0);
	return ret;
}