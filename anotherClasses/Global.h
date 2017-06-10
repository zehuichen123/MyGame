#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "cocos2d.h"
#include "Singleton.h"
#include "defenderGameLayer.h"
#include "Enemy.h"
USING_NS_CC;

//declare these class,or will report error
class defenderGameLayer;
class Enemy;

class Global :public Singleton<Global> {
public:
	Global();
	~Global();

	defenderGameLayer* GdefenderGameLayer;
	Scene* Gscene;
	Sprite* Gmatrix;
	__Array* Genemy;
	__Array* Gbullet;
	__Array* GtoDeleteEnemy;
	__Array* GtoDeleteBullet;
	//bool Gavail;
};
#define global Global::instance()
#endif