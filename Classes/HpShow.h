#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class HpShow :public Node {
public:
	HpShow();
	~HpShow();
	virtual bool init();
	CREATE_FUNC(HpShow);
	void update(float dt);
private:
	ProgressTimer* _real;
};