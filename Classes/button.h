#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class Button :public Layer {
public:
	Button();
	~Button();
	virtual bool init();
	bool onTouchBegan(Touch * touch, Event * event);
	void onTouchEnded(Touch * touch, Event * event);
	void onTouchMoved(Touch * touch, Event * event);
	void updateHero(Touch * touch);
	CREATE_FUNC(Button);
	

private:
	Sprite* MoveLeft;
	Sprite* MoveRight;
	Sprite* MoveUp;
	Sprite* MoveDown;
	Vec2 Direction;
};

