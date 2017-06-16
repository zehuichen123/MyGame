#include "gameOverLayer.h"
#include "defenderGameLayer.h"
using namespace cocos2d;
gameOverLayer::gameOverLayer(void)
{
}
gameOverLayer::~gameOverLayer(void)
{
}
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
		auto pbg=Sprite::create("gmbg/gameoverbg.png");
		pbg->setAnchorPoint(Point(0.5, 0.5));
		pbg->setPosition(getWinCenter());
		this->addChild(pbg, 1);
		pbg->setOpacity(10);

		auto pgameover = Sprite::create("game/gameover.png");
		pgameover->setPosition(getWinCenter());
		this->addChild(pgameover, 2);

		auto pgameovertips = Sprite::create("game/gameovertips.png");
		pgameovertips->setPosition(getWinCenter());
		pgameovertips->setPositionY(pgameovertips->getPositionY() + pgameover->getContentSize().height);
		this->addChild(pgameovertips, 3);

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

