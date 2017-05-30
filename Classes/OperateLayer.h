#pragma once
#include "cocos2d.h"
#include "Global.h"
#include "SkillButton.h"
#include "PopupLayer.h"
#include "GamePause.h"
#include "ui/CocosGUI.h"
using namespace ui;
USING_NS_CC;
class OperateLayer :public Layer {
public:
	OperateLayer();
	~OperateLayer();
	virtual bool init();
	CREATE_FUNC(OperateLayer);
	void attackButton(Ref* pSender);
};