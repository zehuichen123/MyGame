#pragma once
#ifndef __GAMEOVERDIALOG_LAYER_H__
#define __GAMEOVERDIALOG_LAYER_H__
#include "BaseLayer.h"
class gameOverLayer : public BaseLayer
{
public:
	gameOverLayer();
	~gameOverLayer();
	virtual bool init();
	static Scene* createScene();
	bool setUpdateView();
	CREATE_FUNC(gameOverLayer);
	void onEnter();
	virtual bool onTouchBegan(Touch *touch,Event *event);
};
#endif