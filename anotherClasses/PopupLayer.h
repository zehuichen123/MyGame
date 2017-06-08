#pragma once
#include "cocos2d.h"
#include "BarrierLayer.h"
USING_NS_CC;
class PopupLayer :public Layer {
public:
	PopupLayer();
	~PopupLayer();
	bool init(Layer* target);
	static PopupLayer* create(Layer* target);
	void pauseScene(Node* pSender);
	Action* getAction();
};