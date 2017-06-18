#include "coderNameLayer.h"
coderNameLayer::coderNameLayer()
{
	CCLOG("coderNameOn");
}
coderNameLayer::~coderNameLayer()
{
	CCLOG("coderNameOff");
}
Scene* coderNameLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = coderNameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool coderNameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		CC_BREAK_IF(!setUpdateView());
		ret = true;
	} while (0);
	return ret;
}

bool coderNameLayer::setUpdateView()
{
	bool ret = false;
	do {
		auto coderName = Sprite::create("coderName.png");
		coderName->setPosition(getWinCenter());
		this->addChild(coderName);

		auto returnButton = MenuItemSprite::create(
							Sprite::create("gmme/return_up.png"),
							Sprite::create("gmme/return_down.png"),
							CC_CALLBACK_1(coderNameLayer::MenuCallBack, this));
		returnButton->setPosition(Point(getWinSize().width - returnButton->getContentSize().width/2,
									returnButton->getContentSize().height/2));

		auto pMenu = Menu::create(returnButton,NULL);
		pMenu->setPosition(Point::ZERO);
		this->addChild(pMenu);
		ret = true;
	} while (0);
	return ret;
}

void coderNameLayer::MenuCallBack(Ref* pSener)
{
	auto scene = welcomeLayer::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.5f, scene));
}
