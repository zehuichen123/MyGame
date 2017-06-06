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
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
	}
	else 
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/dt.mp3");
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

		Menu* pMenu = CCMenu::create(musicToggleMenuItem, NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu, 2);
		ret = true;
	} while (0);
	return ret;
}

void welcomeLayer::videoCallBack(Ref* pSender) 
{
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	if (soundToggleMenuItem->getSelectedIndex() == 1)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("music/dt.mp3");
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/dt.mp3");
	}
	
}