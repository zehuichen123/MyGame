#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class OperateLayer :public Layer {
public:
	OperateLayer();
	~OperateLayer();
	virtual bool init();
	CREATE_FUNC(OperateLayer);
	void attackButton(Ref* pSender);
};