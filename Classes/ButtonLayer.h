#pragma once
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ButtonLayer :public Layer {
public:
	ButtonLayer();
	~ButtonLayer();
	virtual bool init();
	bool onTouchBegan(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
	void onTouchMoved(Touch * touch, Event * event);
	void updateHero(Touch * touch);
	CREATE_FUNC(ButtonLayer);


private:
	Sprite* MoveLeft;
	Sprite* MoveRight;
	Sprite* MoveUp;
	Sprite* MoveDown;
	Vec2 Direction;
};

