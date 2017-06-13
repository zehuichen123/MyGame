#include "GameSuccessfullyLayer.h"
#include "DefenderGameLayer.h"
USING_NS_CC;
CCScene* GameSuccessfullyLayer::createScene() {
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
	bool isRet = false;
	do
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		char temp[12];
		// 添加背景图片
		auto laybg=Sprite::create("gmbg/stats_bg.png");
		laybg->setScale(1.3);
		CC_BREAK_IF(!laybg);
		laybg->setPosition(getWinCenter());
		this->addChild(laybg);
		// 添加当前关卡
		auto stage = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!stage);
		int lve = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
		sprintf(temp, "%d", lve);
		stage->setString(temp);
		stage->setAnchorPoint(Point(0, 0));
		stage->setPosition(visibleSize.width/2,visibleSize.height*775/970+visibleSize.height/50);
		this->addChild(stage, 1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("lve", lve + 1);

		// 添加击杀怪物数目
		auto killcount = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!killcount);
		int killtemp = UserDefault::sharedUserDefault()->getIntegerForKey("killtemp", 10);
		sprintf(temp, "%d", killtemp);
		killcount->setString(temp);
		killcount->setAnchorPoint(Point(0, 0));
		killcount->setPosition(visibleSize.width *53/100, visibleSize.height * 68/97);
		this->addChild(killcount, 1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("killtemp", 0);


		// 显示剩余生命值
		auto lifecount = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!lifecount);
		int lifetemp = UserDefault::sharedUserDefault()->getIntegerForKey("lifetemp", 100);
		sprintf(temp, "%d", lifetemp);
		lifecount->setString(temp);
		lifecount->setAnchorPoint(Point(0, 0));
		lifecount->setPosition(visibleSize.width *51/100, visibleSize.height * 59/97);
		this->addChild(lifecount, 1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("lifetemp", 100);

		// 显示击杀奖励 规定杀死一个怪经历1个金币
		auto killbound = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!killbound);
		sprintf(temp, "%d", killtemp);
		killbound->setString(temp);
		killbound->setAnchorPoint(Point(0, 0));
		killbound->setPosition(visibleSize.width * 55 / 100, visibleSize.height * 450/970 );
		this->addChild(killbound, 1);

		// 显示生命值奖励 一点生命值奖励一个金币
		auto lifebound = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!lifebound);
		sprintf(temp, "%d", lifetemp);
		lifebound->setString(temp);
		lifebound->setAnchorPoint(Point(0, 0));
		lifebound->setPosition(visibleSize.width * 55 / 100, visibleSize.height * 35/97);
		this->addChild(lifebound, 1);


		// 显示关卡奖励 一个过一关奖励5个金币
		auto goldbound = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!goldbound);
		sprintf(temp, "%d", lve * 5);
		goldbound->setString(temp);
		goldbound->setAnchorPoint(Point(0, 0));
		goldbound->setPosition(visibleSize.width * 55/ 100, visibleSize.height * 26/97 );
		this->addChild(goldbound, 1);


		// 显示显示总奖励金币
		auto total = LabelAtlas::create("0", "game/numWhite.png", 34, 43, '0');
		CC_BREAK_IF(!total);
		int totalnum = lve * 5 + lifetemp + killtemp;
		sprintf(temp, "%d", totalnum);
		total->setString(temp);
		total->setAnchorPoint(Point(0, 0));
		total->setPosition(visibleSize.width * 51 / 100, visibleSize.height * 14/97 );
		this->addChild(total, 1);

		// 加上总金币
		int goldnum = UserDefault::sharedUserDefault()->getIntegerForKey("goldNum", 0);
		UserDefault::sharedUserDefault()->setIntegerForKey("goldNum", totalnum + goldnum);

		// 创建当前提示信息

		auto tip = Sprite::create("game/statstip.png");
		CC_BREAK_IF(!tip);
		tip->setPosition(ccp(this->getContentSize().width / 2, 30));
		this->addChild(tip, 1);
		tip->runAction(RepeatForever::create(Blink::create(1, 1)));


		isRet = true;
	} while (0);
	return isRet;
}
GameSuccessfullyLayer::GameSuccessfullyLayer() {

}
GameSuccessfullyLayer::~GameSuccessfullyLayer() {

}

void GameSuccessfullyLayer::onEnter() {
	BaseLayer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameSuccessfullyLayer::onTouchBegan, this);
	this->setSwallowsTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool GameSuccessfullyLayer::onTouchBegan(Touch *touch,Event *event) {
	auto se = defenderGameLayer::createScene();
	//CCScene* se=GameSuccessfullyLayer::scene();
	Director::getInstance()->replaceScene(TransitionSlideInR::create(1, se));
	return true;
}

void GameSuccessfullyLayer::onExit() {
	BaseLayer::onExit();
}