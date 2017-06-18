#ifndef  __CHECKPOINT_SYSTEMS_H__
#define  __CHECKPOINT_SYSTEMS_H__
#include "cocos2d.h"
USING_NS_CC;
//¹Ø¿¨ÏµÍ³
class   ChangeSystem {
public:
	ChangeSystem();
	~ChangeSystem();
	static int hurtImprove();						// improve the enmey's ATK
	static int speedImprove();						//improve the enmey's movespeed
	static float defendImprove();					//improve the enemy's defensive power
};
#endif   