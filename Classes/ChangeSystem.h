#ifndef  __CHECKPOINT_SYSTEMS_H__
#define  __CHECKPOINT_SYSTEMS_H__
#include "cocos2d.h"
USING_NS_CC;
//关卡系统
class   ChangeSystem {
public:
	ChangeSystem();
	~ChangeSystem();
	//根据怪物类型和当前等级 获取怪物的伤害提升值
	static int hurtImprove(); // 传入参数怪物类型
	static int speedImprove();//根据关卡和怪物类型获获取提升能力值
	static float defendImprove();

};
#endif   