#include "gameOverLayer.h"
#include "defenderGameLayer.h"
USING_NS_CC;
gameOverLayer::gameOverLayer(void)
{}
gameOverLayer::~gameOverLayer(void)
{}

bool gameOverLayer::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!this->setUpdateView());
		ret = true;
	} while (0);

	return ret;
}

Scene* gameOverLayer::createScene()
{
	auto scene = Scene::create();
	auto GameOverLayer = gameOverLayer::create();
	scene->addChild(GameOverLayer);
	return scene;
}

bool gameOverLayer::setUpdateView()
{
	bool isRet = false;
	do
	{
		auto GameOverBg=Sprite::create("gmbg/gameoverbg.png");
		GameOverBg->setAnchorPoint(Point(0.5, 0.5));
		GameOverBg->setPosition(getWinCenter());
		this->addChild(GameOverBg, 1);
		GameOverBg->setOpacity(100);

		//create gameover tips 
		auto GameOver = Sprite::create("game/gameover.png");
		GameOver->setPosition(getWinCenter());
		this->addChild(GameOver, 2);

		auto gameoverTips = Sprite::create("game/gameovertips.png");
		gameoverTips->setPosition(getWinCenter());
		gameoverTips->setPositionY(gameoverTips->getPositionY() +2* gameoverTips->getContentSize().height);
		this->addChild(gameoverTips, 3);

		isRet = true;
	} while (0);
	return isRet;

}

void gameOverLayer::onEnter()
{
	BaseLayer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(gameOverLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool gameOverLayer::onTouchBegan(Touch *touch, Event *event) 
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,defenderGameLayer::createScene()));
	return true;
}

