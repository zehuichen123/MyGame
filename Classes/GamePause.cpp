#include "GamePause.h"
GamePause::GamePause()
{}
GamePause::~GamePause()
{}
bool GamePause::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		CC_BREAK_IF(!this->setUpdateView());
		ret = true;
	} while (0);
	return ret;
}

bool GamePause::setUpdateView()
{
	bool ret = false;
	do {
		auto pauseBg = Sprite::create("gmbg/pause_bg.png");
		pauseBg->setScale(1.3);
		pauseBg->setPosition(getWinCenter());
		this->addChild(pauseBg);

		//create a button back to the welcomeLayer
		auto homeBack = MenuItemSprite::create(
			Sprite::create("gmme/btn_home_up.png"),
			Sprite::create("gmme/btn_home_down.png"),
			CC_CALLBACK_1(GamePause::homeCallBack, this));
		homeBack->setAnchorPoint(Point(1, 0.5));
		homeBack->setPosition(getWinCenter());
		homeBack->setPositionX(homeBack->getPosition().x - 80);

		//create a resume button
		auto resumeBack = MenuItemSprite::create(
			Sprite::create("gmme/btn_resume_up.png"),
			Sprite::create("gmme/btn_resume_down.png"),
			CC_CALLBACK_1(GamePause::resumeCallBack, this));
		resumeBack->setAnchorPoint(Point(0.5, 0.5));
		resumeBack->setPosition(getWinCenter());

		//create a retry button
		auto retryBack = MenuItemSprite::create(
			Sprite::create("gmme/btn_retry_up.png"),
			Sprite::create("gmme/btn_retry_down.png"),
			CC_CALLBACK_1(GamePause::retryCallBack, this));
		retryBack->setAnchorPoint(Point(0,0.5));
		retryBack->setPosition(getWinCenter());
		retryBack->setPositionX(retryBack->getPosition().x + 80);

		auto _Menu = Menu::create(homeBack,resumeBack,retryBack,NULL);
		_Menu->setPosition(Point::ZERO);
		this->addChild(_Menu);
		
		ret = true;
	} while (0);
	return ret;
}

void GamePause::homeCallBack(Ref* pSender)
{
	Scene* scene = welcomeLayer::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, scene));
	Director::getInstance()->resume();
}

void GamePause::resumeCallBack(Ref* pSender)
{
	this->getParent()->removeFromParent();
	Director::getInstance()->resume();
}

void GamePause::retryCallBack(Ref* pSender)
{
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, defenderGameLayer::createScene()));
}