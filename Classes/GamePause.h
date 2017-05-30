#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GamePause :public Layer {
public:
	GamePause();
	~GamePause();
	bool init();
	CREATE_FUNC(GamePause);
};