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
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *event);
	static Scene* createScene();
	CREATE_FUNC(gameOverLayer);
private:
	bool setUpdateView();
};
#endif