#pragma once
#include "cocos2d.h"
#include "MapLayer.h"
USING_NS_CC;
class GameLayer :public Layer {
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	void addHero();
	void addEnemies();
	void update(float dt);
	void updateHero();
	void updateEnemy();
private:
	Size visibleSize;
	Vec2 visibleOrigin;
};