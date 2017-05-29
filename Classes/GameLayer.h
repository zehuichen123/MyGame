#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_
#include "cocos2d.h"
USING_NS_CC;
#include "MapLayer.h"
#include "Global.h"
#include "Hero.h"

class Hero;
class GameLayer : public Layer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();

	void addHero();

	void update(float dt);
	void updateHero(float dt);

	CC_SYNTHESIZE_READONLY(Hero*, m_pHero, Hero);
	CREATE_FUNC(GameLayer);

private:
	Size _visibleSize;
	Vec2 _visibleOrigin;
};

#endif