#ifndef  __CHECKPOINT_SYSTEMS_H__
#define  __CHECKPOINT_SYSTEMS_H__
#include "cocos2d.h"
USING_NS_CC;
//�ؿ�ϵͳ
class   ChangeSystem {
public:
	ChangeSystem();
	~ChangeSystem();
	//���ݹ������ͺ͵�ǰ�ȼ� ��ȡ������˺�����ֵ
	static int hurtImprove(); // ���������������
	static int speedImprove();//���ݹؿ��͹������ͻ��ȡ��������ֵ
	static float defendImprove();

};
#endif   