#ifndef __GAMETIPS_SPRITE_H__
#define __GAMETIPS_SPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
// ������Ҫ��������Ϸ����״̬����ʾ
class GameTipsSprite :public Node
{
public:
	GameTipsSprite();
	~GameTipsSprite();
	CREATE_FUNC(GameTipsSprite);
	virtual bool init();
	bool setUpdateView();
	void initialization();
	void setgoldNum(int num);
	void setMonstNum(int num);
	void setMonstTotalNum(int num);
	void setStageNum(int num);
};
#endif