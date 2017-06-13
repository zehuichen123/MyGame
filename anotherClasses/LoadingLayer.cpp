#include "LoadingLayer.h"
LoadingLayer::LoadingLayer()
{
	loadingNum = 0;
	totalNum = 9;
};
LoadingLayer::~LoadingLayer()
{};

Scene* LoadingLayer::createScene() 
{
	Scene* scene = CCScene::create();
	LoadingLayer* layer = LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		CC_BREAK_IF(!this->setUpdateView());
		CCTextureCache::getInstance()->addImageAsync
					("gmbg/loadingbg.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this));
		CCTextureCache::getInstance()->addImageAsync
					("gmbg/welcomebg.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 欢迎界面 背景图片
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmbg/coder.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 添加关于开发者背景图片
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmme/button_sound_on.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 欢迎界面 声音开始
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmme/button_sound_off.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 欢迎界面 声音关闭
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmme/coder_up.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 欢迎界面 开发者按钮
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmme/coder_down.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 欢迎界面 开发者按钮
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmme/return_down.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 返回菜单按钮
		//this->loadCallBack();
		CCTextureCache::getInstance()->addImageAsync
					("gmme/return_up.png",CC_CALLBACK_0(LoadingLayer::loadCallBack,this)); // 返回菜单按钮
		//this->loadCallBack();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("specia/thumbnails.plist", "specia/thumbnails.png");
		ret = true;
	} while (0);
	return ret;
}
bool LoadingLayer::setUpdateView()
{
	bool ret = false;
	do {
		float vecx = getWinSize().width / 2 +getWinOrigin().x;
		float vecy = getWinSize().height / 2 + getWinOrigin().y;
		auto backGround = Sprite::create("gmbg/loadingbg.png");
		backGround->setPosition(Point(vecx, vecy));
		this->addChild(backGround,1);

		auto loadimg = Sprite::create("gmbg/loading.png");
		loadingProcess = ProgressTimer::create(loadimg);
		loadingProcess->setType(ProgressTimer::Type::BAR);
		loadingProcess->setMidpoint(Point(0, 0));
		loadingProcess->setBarChangeRate(Point(1, 0));
		loadingProcess->setPosition(Point(vecx, vecy-3));
		this->addChild(loadingProcess,2);

		ret = true;
	} while (0);
	return ret;
}

void LoadingLayer::loadCallBack()
{
	loadingNum++;
	float now = loadingProcess->getPercentage();
	loadingProcess->setPercentage(100/totalNum+now);
	if(loadingNum<totalNum)
	{}
	else
	{
		CCLOG("LOADING_OVER");
		goWelcomeLayer();
	}
}

void LoadingLayer::goWelcomeLayer()
{
	Director::getInstance()->replaceScene(TransitionFadeDown::create(0.01f,welcomeLayer::createScene()));
}