#include "MapLayer.h"
#include <iostream>
USING_NS_CC;

MapLayer::MapLayer():
	m_map(nullptr),
	m_player(nullptr),
	_meta(nullptr),
	_food(nullptr)
{
}

MapLayer::~MapLayer()
{
}

Scene* MapLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	auto indexLayer = Layer::create();
	global->GindexLayer = indexLayer;
    // 'layer' is an autorelease object
    auto layer = MapLayer::create();

	
    // add layer as a child to scene
    scene->addChild(layer);
	scene->addChild(indexLayer,5);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//add the map
	m_map = CCTMXTiledMap::create("mmap.tmx");
	m_map->setPosition(0, 0);
	addChild(m_map, -1);

	//add a player
	auto objects = m_map->objectGroupNamed("hero");
	auto spawnPoint = objects->getObject("hero");
	float fPosX = spawnPoint.at("x").asFloat();
	float fPosY = spawnPoint.at("y").asFloat();

	//set the position of player
	m_player = Player::createWithMap(this);
	fPosX += m_map->getTileSize().width / 2;
	fPosY += m_map->getTileSize().height / 2;

	m_player->setPosition(fPosX, fPosY);

	this->addChild(m_player);

	//create a menu button to return welcomelayer
	home = MenuItemSprite::create(
		Sprite::create("gmme/btn_home_up.png"),
		Sprite::create("gmme/btn_home_down.png"),
		CC_CALLBACK_1(MapLayer::homeCallBack, this));
	home->setAnchorPoint(Point(0, 1));
	auto visiSize = Director::getInstance()->getVisibleSize();
	home->setPosition(20, visiSize.height - 20);

	//create a touch events litener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch *pTouch, Event *pEvent)->bool 
	{ 
		if (m_player->getAvail())
		{
			CCLOG("yse");
		}
		if (m_player->getAvail())
		{
			auto touchLocation = pTouch->getLocation();
			//auto touchPos = this->tileCoordForPosition(touchLocation);
			m_player->setAvail(false);
			CCLOG("setAvailfalse");
			Point touchPos = m_map->convertToNodeSpace(touchLocation);

			//the player move to the target
			m_player->moveToward(touchPos);
			CCLOG("ARRIVED");
			return true;
		}
		else
		{
			return false;
		}
	 };
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();

	//add menu
	auto _Menu = Menu::create(home, NULL);
	_Menu->setPosition(Point::ZERO);
	global->GindexLayer->addChild(_Menu, 4);

	//get the meta layer of the tiledmap
	_meta = m_map->getLayer("meta");
	_meta->setVisible(false);
	_food = m_map->getLayer("food");

    return true;
}

void MapLayer::setViewPosition(Point pos)
{
	//get winSize
	Size winSize = Director::sharedDirector()->getWinSize();
	float fX = std::max(pos.x, winSize.width / 2);
	float fY = std::max(pos.y, winSize.height / 2);

	fX = std::min(fX, (m_map->getMapSize().width * m_map->getTileSize().width - winSize.width / 2));
	fY = std::min(fY,(m_map->getMapSize().height * m_map->getTileSize().height - winSize.height / 2));

	auto actPos = Point(fX, fY);
	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actPos;

	//set the view position
	this->setPosition(viewPoint);
}

//get the position for tile coord 
Point MapLayer::tileCoordForPosition(const Point &pos)
{
	int iX = pos.x / m_map->getTileSize().width;
	int iY = ((m_map->getMapSize().height * m_map->getTileSize().height) - pos.y) / m_map->getTileSize().height;

	return Point(iX, iY);
}

Point MapLayer::positionForTileCoord(const Point &tileCoord) {
	int x = (tileCoord.x * m_map->getTileSize().width) + m_map->getTileSize().width / 2;
	int y = (m_map->getMapSize().height * m_map->getTileSize().height) -
		(tileCoord.y * m_map->getTileSize().height) - m_map->getTileSize().height / 2;
	return Point(x, y);
}

//judge the propoties of tiles
bool MapLayer::isPropTile(const char * prop, cocos2d::Point & tilePos, TMXLayer * pLayer)
{
	//check if the tile is valid
	if (!this->isValidTileCoord(tilePos))
	{
		return false;
	}
	//get the gid of tile
	auto tileGid = pLayer->getTileGIDAt(tilePos);
	//get properties of tile
	auto properties = m_map->getPropertiesForGID(tileGid);
	//if there isn't any properties, return false
	if (properties.isNull())
	{
		return false;
	}
	//if there are properties, check the prop is true or not
	return properties.asValueMap().find(prop) != properties.asValueMap().end();
}

//if the tile coord is valid
bool MapLayer::isValidTileCoord(const Point &tileCoord) 
{
	if (tileCoord.x < 0 || tileCoord.y < 0 ||
		tileCoord.x >= m_map->getMapSize().width ||
		tileCoord.y >= m_map->getMapSize().height) {
		return false;
	}
	else 
	{
		return true;
	}
}

//judge if the tlie is barrier
bool MapLayer::isBarrierTile(cocos2d::Point & tilePos)
{
	return isPropTile("Collidable", tilePos, _meta);
}

//judge if the tile  is food
bool MapLayer::isFoodTile(cocos2d::Point & tilePos)
{
	return isPropTile("Collectable", tilePos, _meta);
}

//remove the food tile
void MapLayer::removeTheFood(cocos2d::Point & tilePos)
{
	_food->removeTileAt(tilePos);
}

//get the walkable tile coord adjacent to the current tile coord
cocos2d::PointArray * MapLayer::walkableAdjacentTileCoord(const cocos2d::Point & tileCoord)
{
	//create an array to store the walkable tile coord
	PointArray * temp = PointArray::create(4);

	Point p;
	//directions
	int dir[4][2] = {{0,-1}, {-1,0 }, {0,1 }, {1,0 }};

	//check the adjacent tile
	for (size_t i = 0; i < 4; i++)
	{
		p.setPoint(tileCoord.x + dir[i][0], tileCoord.y + dir[i][1]);
		if (this->isValidTileCoord(p) && !this->isBarrierTile(p))
		{
			temp->addControlPoint(p);
		}
	}

	return temp;
}

//update the view Position
void MapLayer::update(float delta)
{
	this->setViewPosition(m_player->getPosition());
}

//menu close callback function
void MapLayer::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

//return welcome layer
void MapLayer::homeCallBack(cocos2d::Ref * pSender)
{
	Scene* scene = welcomeLayer::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.5, scene));
	Director::getInstance()->resume();
}
