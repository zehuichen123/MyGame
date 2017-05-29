#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class MapLayer :public Layer {
public:
	MapLayer();
	~MapLayer();
	virtual bool init();
	void update(float dt);
	void setViewPointCenter(Point pos);
	CREATE_FUNC(MapLayer);
};