#include "ChangeSystem.h"
// ���������������
int ChangeSystem::hurtImprove() 
{
	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	return i;

}
//���ݹؿ��͹������ͻ��ȡ��������ֵ
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
	//���ӹ���ĵֿ���
	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	return i*0.01;
}