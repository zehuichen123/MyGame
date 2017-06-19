#ifndef __MAPLAYER_H__
#define __MAPLAYER_H__

#include "cocos2d.h"
#include "player.h"
#include "welcomeLayer.h"
#include "Global.h"
class Player;

class MapLayer : public cocos2d::Layer
{
public:
	MapLayer();
	~MapLayer();
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void setViewPosition(cocos2d::Point pos);

	//void onTouchEnded(cocos2d::Touch *pTouches, cocos2d::Event *pEvents);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void homeCallBack(cocos2d::Ref* pSender);

	cocos2d::Point tileCoordForPosition(const cocos2d::Point &pos);

	cocos2d::Point positionForTileCoord(const cocos2d::Point & tileCoord);

	//void checkTileCoord(cocos2d::Point pos);

	bool isPropTile(const char * prop, cocos2d::Point & tilePos, cocos2d::TMXLayer * pLayer);
	bool isValidTileCoord(const cocos2d::Point & tileCoord);
	bool isBarrierTile(cocos2d::Point & tilePos);
	bool isFoodTile(cocos2d::Point & tilePos);

	void removeTheFood(cocos2d::Point & tilePos);

	cocos2d::PointArray * walkableAdjacentTileCoord(const cocos2d::Point &tileCoord);

	virtual void update(float delta);

    // implement the "static create()" method manually
    CREATE_FUNC(MapLayer);

private:
	cocos2d::TMXTiledMap *m_map;
	Player * m_player;
	cocos2d::TMXLayer *_meta;
	cocos2d::TMXLayer *_food;
	cocos2d::MenuItemSprite * home;
};

#endif // __HELLOWORLD_SCENE_H__
