#include "ChangeSystem.h"
// ���������������
int ChangeSystem::hurtImprove() 
{
	//�������� ÿʮ�� �˺�ֵ����һ��  // ����Ŀǰֻ��һ�ֹ��� ����Լ����ݲ�ͬ�Ĺ����������

	int i = UserDefault::sharedUserDefault()->getIntegerForKey("lve", 1);
	int temp = i / 10;
	return temp;

}
//���ݹؿ��͹������ͻ��ȡ��������ֵ
int ChangeSystem::speedImprove()
{
	//�������� ÿʮ�� �ٶ� ���� һ �� 

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