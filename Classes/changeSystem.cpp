#include "ChangeSystem.h"
// 传入参数怪物类型
int ChangeSystem::hurtImprove() 
{
	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	return i;

}
//根据关卡和怪物类型获获取提升能力值
int ChangeSystem::speedImprove()
{
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