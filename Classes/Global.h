#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "cocos2d.h"
#include "Singleton.h"
#include "GameLayer.h"
#include "StateLayer.h"
#include "OperateLayer.h"
USING_NS_CC;

//declare these class,or will report error
class GameLayer;
class StateLayer;
class OperateLayer;

class Global :public Singleton<Global> {
public:
	Global();
	~Global();

	GameLayer* gameLayer;
	OperateLayer* operateLayer;
	StateLayer* stateLayer;
	TMXTiledMap* tileMap;
};
#define global Global::instance()
#endif