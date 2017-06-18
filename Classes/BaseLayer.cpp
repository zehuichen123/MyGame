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
		ret = true;
	} while (0);
	return ret;
}
Size BaseLayer::getWinSize() {
	return	Director::sharedDirector()->getVisibleSize();
}
Point BaseLayer::getWinOrigin() {
	return Director::sharedDirector()->getVisibleOrigin();
}

Point BaseLayer::getWinCenter() {
	return	Point(getWinSize().width / 2 + getWinOrigin().x, getWinSize().height / 2 + getWinOrigin().y);
}

