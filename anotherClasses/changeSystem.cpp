#include "ChangeSystem.h"
// 传入参数怪物类型
int ChangeSystem::hurtImprove() 
{
	//我们设置 每十关 伤害值提升一点  // 由于目前只有一种怪物 这个自己根据不同的怪物进行适配

	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	int temp = i / 10;
	return temp;

}
//根据关卡和怪物类型获获取提升能力值
int ChangeSystem::speedImprove()
{
	//我们设置 每十关 速度 提升 一 点 

	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	int temp = i *10;

	if (temp >= 100) {
		temp = 100;
	}

	return temp;
}

float ChangeSystem::defendImprove()
{
	//增加怪物的抵抗力
	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	return i*0.01;
}