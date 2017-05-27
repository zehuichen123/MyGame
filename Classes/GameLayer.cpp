#include "GameLayer.h"
GameLayer::GameLayer(){}
GameLayer::~GameLayer(){}
bool GameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		//add code here
		visibleSize = Director::getInstance()->getVisibleSize();
		visibleOrigin = Director::getInstance()->getVisibleOrigin();

		//add SpriteFrame to SpriteFrameCache for convenience and quick speed
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boy.plist", "Boy.pvr.ccz");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy.plist", "Enemy.pvr.ccz");

		auto mapLayer = MapLayer::create();
		this->addChild(mapLayer, -100);

		
		ret = true;
	} while (0);
	return ret;
}