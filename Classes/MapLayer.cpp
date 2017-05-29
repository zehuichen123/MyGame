#include "MapLayer.h"
MapLayer::MapLayer() {};
MapLayer::~MapLayer() {};
bool MapLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		auto tileMap = TMXTiledMap::create("mymap.tmx");
		tileMap->setPosition(Vec2(0, 0));
		global->tileMap = tileMap;
		this->addChild(tileMap);
		ret = true;
	} while (0);
	this->scheduleUpdate();
	return ret;
}
/*update the view to keep the hero at the center of screen*/
void MapLayer::update(float dt)
{
	this->setViewPointCenter(global->hero->getPosition());
}
void MapLayer::setViewPointCenter(Point pos)
{
	Size ScreenSize = Director::getInstance()->getWinSize();
	auto _map = global->tileMap;

	//if hero's pos<middle of screen,set pos=middle of screen
	int x = MAX(pos.x, ScreenSize.width / 2);
	int y = MAX(pos.y, ScreenSize.height / 2);

	//if hero's pos>max size(avoiding appearing black lines),set pos=max size
	x = MIN(x, (_map->getMapSize().width*_map->getTileSize().width) - ScreenSize.width / 2);
	y = MIN(y, (_map->getMapSize().height*_map->getTileSize().height) - ScreenSize.height / 2);

	//pos we should set
	Point NormalPosition = Vec2(x, y);

	//the actual pos we need to move
	Point centerView = Vec2(ScreenSize.width / 2, ScreenSize.height / 2);
	Point ViewPoint = centerView = centerView - NormalPosition;

	//set the map's final pos
	this->getParent()->setPosition(ViewPoint);
}