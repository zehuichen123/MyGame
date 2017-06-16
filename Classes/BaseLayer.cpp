#include "BaseLayer.h"
Scene* BaseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = BaseLayer::create();
	scene->addChild(layer);
	return scene;
}
bool BaseLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		//visibleSize = Director::getInstance()->getVisibleSize();
		//visibleOrigin = Director::getInstance()->getVisibleOrigin();
		ret = true;
	} while (0);
	return ret;
}
Size BaseLayer::getWinSize() {
	return	CCDirector::sharedDirector()->getVisibleSize();
}
Point BaseLayer::getWinOrigin() {
	return CCDirector::sharedDirector()->getVisibleOrigin();
}

Point BaseLayer::getWinCenter() {
	return	ccp(getWinSize().width / 2 + getWinOrigin().x, getWinSize().height / 2 + getWinOrigin().y);
}

