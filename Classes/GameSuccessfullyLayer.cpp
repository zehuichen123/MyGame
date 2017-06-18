#include "GameSuccessfullyLayer.h"
#include "DefenderGameLayer.h"
USING_NS_CC;
GameSuccessfullyLayer::GameSuccessfullyLayer()
{}
GameSuccessfullyLayer::~GameSuccessfullyLayer() 
{}
CCScene* GameSuccessfullyLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSuccessfullyLayer::create();
	scene->addChild(layer);
	return scene;
}
bool GameSuccessfullyLayer::init() {
	bool ret = false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateView());
		ret = true;
	} while (0);
	return ret;
}
bool GameSuccessfullyLayer::setUpdateView() {
	bool ret = false;
	do
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		char temp[12];
		// add background pic
		auto laybg=Sprite::create("gmbg/stats_bg.png");
		laybg->setScale(1.3);
		CC_BREAK_IF(!laybg);
		laybg->setPosition(getWinCenter());
		this->addChild(laybg);
		// add current level
		auto stage = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!stage);
		int lve = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);			//get it from the userDefault
		sprintf(temp, "%d", lve);
		stage->setString(temp);
		stage->setAnchorPoint(Point(0, 0));
		stage->setPosition(visibleSize.width/2,visibleSize.height*74/97);
		this->addChild(stage, 1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("lve", lve + 1);

		// the amount of monsters you've killed
		auto killcount = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!killcount);
		int killtemp = UserDefault::sharedUserDefault()->getIntegerForKey("killtemp", 10);
		sprintf(temp, "%d", killtemp);
		killcount->setString(temp);
		killcount->setAnchorPoint(Point(0, 0));
		killcount->setPosition(visibleSize.width *53/100, visibleSize.height * 64/97);
		this->addChild(killcount, 1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("killtemp", 0);


		// show the current life value
		auto lifecount = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!lifecount);
		int lifetemp = UserDefault::sharedUserDefault()->getIntegerForKey("lifetemp", 100);
		sprintf(temp, "%d", lifetemp);
		lifecount->setString(temp);
		lifecount->setAnchorPoint(Point(0, 0));
		lifecount->setPosition(visibleSize.width *51/100, visibleSize.height * 55/97);
		this->addChild(lifecount, 1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("lifetemp", 100);

		// show the award of kill num£¨»÷É±½±Àø£©
		auto killbound = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!killbound);
		sprintf(temp, "%d", killtemp);
		killbound->setString(temp);
		killbound->setAnchorPoint(Point(0, 0));
		killbound->setPosition(visibleSize.width * 55 / 100, visibleSize.height * 420/970 );
		this->addChild(killbound, 1);

		// show the award of remained life value(ÉúÃüÖµ½±Àø£©
		auto lifebound = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!lifebound);
		sprintf(temp, "%d", lifetemp);
		lifebound->setString(temp);
		lifebound->setAnchorPoint(Point(0, 0));
		lifebound->setPosition(visibleSize.width * 55 / 100, visibleSize.height * 32/97);
		this->addChild(lifebound, 1);


		// show the award of current level(¹Ø¿¨½±Àø)
		auto goldbound = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!goldbound);
		sprintf(temp, "%d", lve * 5);
		goldbound->setString(temp);
		goldbound->setAnchorPoint(Point(0, 0));
		goldbound->setPosition(visibleSize.width * 55/ 100, visibleSize.height * 25/97 );
		this->addChild(goldbound, 1);


		//show the total num of award
		auto total = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!total);
		int totalnum = lve * 5 + lifetemp + killtemp;
		sprintf(temp, "%d", totalnum);
		total->setString(temp);
		total->setAnchorPoint(Point(0, 0));
		total->setPosition(visibleSize.width * 51 / 100, visibleSize.height * 13/97 );
		this->addChild(total, 1);

		// sum the total num to the userDefault
		int goldnum = UserDefault::sharedUserDefault()->getIntegerForKey("goldNum", 0);
		UserDefault::sharedUserDefault()->setIntegerForKey("goldNum", totalnum + goldnum);

		//click to continue information
		auto tip = Sprite::create("game/statstip.png");
		CC_BREAK_IF(!tip);
		tip->setPosition(ccp(this->getContentSize().width / 2, 30));
		this->addChild(tip, 1);
		tip->runAction(RepeatForever::create(Blink::create(1, 1)));

		ret = true;
	} while (0);
	return ret;
}

void GameSuccessfullyLayer::onEnter() 
{
	BaseLayer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameSuccessfullyLayer::onTouchBegan, this);
	this->setSwallowsTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameSuccessfullyLayer::onTouchBegan(Touch *touch,Event *event) 
{
	auto nextLevel = defenderGameLayer::createScene();
	Director::getInstance()->replaceScene(TransitionSlideInR::create(1,nextLevel));
	return true;
}

void GameSuccessfullyLayer::onExit() 
{
	BaseLayer::onExit();
}
