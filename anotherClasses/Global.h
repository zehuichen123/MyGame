#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "cocos2d.h"
#include "Singleton.h"
#include "defenderGameLayer.h"
#include "Enemy.h"
#include "cityBloodSprite.h"
USING_NS_CC;

//declare these class,or will report error
class defenderGameLayer;
class Enemy;
class cityBloodSprite;

class Global :public Singleton<Global> {
public:
	Global();
	~Global();

	defenderGameLayer* GdefenderGameLayer;
	cityBloodSprite* GcityBloodSprite;
	Scene* Gscene;
	Sprite* Gmatrix;
	__Array* Genemy;
	__Array* GtoDeleteBullet;
	//bool Gavail;
};
#define global Global::instance()
#endif