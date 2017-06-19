#include "welcomeLayer.h"
welcomeLayer::welcomeLayer()
{};
welcomeLayer::~welcomeLayer()
{};

Scene* welcomeLayer::createScene() {
	Scene* scene = Scene::create();
	welcomeLayer* layer = welcomeLayer::create();
	scene->addChild(layer);
	return scene;
}

bool welcomeLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateView());
		ret = true;
	} while (0);
	return ret;
}

void welcomeLayer::onEnter() {
	BaseLayer::onEnter();
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) 
	{
	}
	else 
	{
		if (UserDefault::sharedUserDefault()->getBoolForKey("isplay", true)) {
			SimpleAudioEngine::getInstance()->playBackgroundMusic("music/dt.mp3", true);
			// °ÑÒôÀÖ×´Ì¬ÉèÖÃÎª²¥·Å×´Ì¬
			UserDefault::sharedUserDefault()->setBoolForKey("isplay", true);
		}
	}
}

bool welcomeLayer::setUpdateView()
{
	bool ret = false;
	do {
		//auto TextureBg = TextureCache::getInstance()->textureForKey("gmbg/welcomebg.png");
		auto SpriteBg = Sprite::create("gmbg/welcomebg.png");
		SpriteBg->setScale(1.3);
		SpriteBg->setPosition(getWinCenter());
		CC_BREAK_IF(!SpriteBg);
		this->addChild(SpriteBg,1);
		//CCLOG("BACKGROUND");


		auto coderName = MenuItemSprite::create(
			Sprite::create("gmme/coder_up.png"),
			Sprite::create("gmme/coder_down.png"),
			CC_CALLBACK_1(welcomeLayer::coderNameCallBack, this));
		coderName->setPosition(Point(getWinSize().width*0.78f, getWinSize().height*0.21f));

		auto playButton = MenuItemSprite::create(
			Sprite::create("gmme/star_up.png"),
			Sprite::create("gmme/star_down.png"),
			CC_CALLBACK_1(welcomeLayer::playCallBack, this));
		//CC_BREAK_IF(!playButton);
		playButton->setPosition(Point(getWinSize().width*0.85f, getWinSize().height*0.76f));

		auto playButton_2 = MenuItemSprite::create(
			Sprite::create("gmme/star_down.png"),
			Sprite::create("gmme/star_up.png"),
			CC_CALLBACK_1(welcomeLayer::play_2CallBcak, this));
		//CC_BREAK_IF(!playButton);
		playButton_2->setPosition(Point(getWinSize().width*0.83f, getWinSize().height*0.56f));

		auto musicOnMenuItem = MenuItemImage::create(
			"gmme/button_sound_on.png",
			"gmme/button_sound_on.png");
		auto musicOffMenuItem = MenuItemImage::create(
			"gmme/button_sound_off.png",
			"gmme/button_sound_off.png");
		auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
										CC_CALLBACK_1(welcomeLayer::videoCallBack, this),
										musicOnMenuItem,
										musicOffMenuItem,
										NULL);
		musicToggleMenuItem->setPosition(Point(getWinSize().width*0.15f, getWinSize().height*0.55f));


		auto exitGame = MenuItemSprite::create(
			Sprite::create("gmme/outup.png"),
			Sprite::create("gmme/outdown.png"),
			CC_CALLBACK_1(welcomeLayer::gameOverCallBack, this));
		//CC_BREAK_IF(!playButton);
		exitGame->setPosition(Point(getWinSize().width*0.8f, getWinSize().height*0.396f));


		Menu* pMenu = CCMenu::create(musicToggleMenuItem, coderName, playButton, playButton_2, exitGame, NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu, 2);
		ret = true;
	} while (0);
	return ret;
}

void welcomeLayer::gameOverCallBack(Ref* pSender)
{
	Director::getInstance()->end();
}
void welcomeLayer::videoCallBack(Ref* pSender) 
{
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	//*********************************************

	//****************IMPORTANT********************

	//*********************************************
	if (soundToggleMenuItem->getSelectedIndex() == 1)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("music/dt.mp3");
		UserDefault::sharedUserDefault()->setBoolForKey("isplay", false);
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/dt.mp3");
		UserDefault::sharedUserDefault()->setBoolForKey("isplay", true);
	}
	
}

void welcomeLayer::coderNameCallBack(Ref* pSender)
{
	auto scene = coderNameLayer::createScene();
	//this->removeAllChildren();
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.5f, scene));
}
void welcomeLayer::playCallBack(Ref* pSender)
{
	auto scene = defenderGameLayer::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, scene));
}

void welcomeLayer::play_2CallBcak(Ref* pSender)
{
	auto scene = MapLayer::createScene();
	Director::getInstance()->replaceScene(scene);

}
