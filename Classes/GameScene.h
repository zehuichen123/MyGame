#pragma once
#include "cocos2d.h"
#include "StateLayer.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "ButtonLayer.h"
USING_NS_CC;
class GameScene :public Scene {
public:
	GameScene();
	~GameScene();
	static Scene* createScene();
};