#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "cocos2d.h"
#include "Singleton.h"
#include "defenderGameLayer.h"
#include "Enemy.h"
#include "GameTips.h"
#include "cityBloodSprite.h"
USING_NS_CC;

//declare these class,or it will report error
class defenderGameLayer;
class Enemy;
class cityBloodSprite;
class GameTipsSprite;

class Global :public Singleton<Global> {
public:
	Global();
	~Global();

	defenderGameLayer* GdefenderGameLayer;
	cityBloodSprite* GcityBloodSprite;
	GameTipsSprite* GgameTipsSprite;
	Scene* Gscene;
	Sprite* Gmatrix;
	__Array* Genemy;
	__Array* GtoDeleteBullet;
	Layer* GindexLayer;
};
#define global Global::instance()
#endif