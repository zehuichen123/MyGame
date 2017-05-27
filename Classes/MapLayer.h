#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MapLayer :public Layer {
public:
	MapLayer();
	~MapLayer();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(MapLayer);
};