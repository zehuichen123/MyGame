#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;
USING_NS_CC;
class GamePause :public Layer {
public:
	GamePause();
	~GamePause();
	bool init();
	CREATE_FUNC(GamePause);
};