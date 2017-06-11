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
	void initialization();// ���³�ʼ������ؼ�
	void setgoldNum(int num);// ���ý��������
	void setMonstNum(int num);// ���õ�ǰ���ﲨ��
	void setMonstTotalNum(int num);// ���õ�ǰ�����ܲ���
	void setStageNum(int num);// ���õ�ǰ�ؿ�
};
#endif