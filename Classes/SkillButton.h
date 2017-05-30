#pragma once
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class SkillButton :public Node {
public:
	SkillButton();
	~SkillButton();
	static SkillButton* create(const char* Nomal, const char* Click, const char* Mask, float CDTime);

	static SkillButton* create(const char* Nomal, const char* Mask, float CDTime)
	{
		return SkillButton::create(Nomal, Nomal, Mask, CDTime);
	};

	static SkillButton* create(const char* Nomal, const char* Mask)
	{
		return SkillButton::create(Nomal, Nomal, Mask, 1.0f);
	};

	static SkillButton* create(const char* Nomal, float CDTime)
	{
		return SkillButton::create(Nomal, Nomal, Nomal, CDTime);
	};

	static SkillButton* create(const char* Nomal)
	{
		return SkillButton::create(Nomal, Nomal, Nomal, 1.0f);
	};
	
	CC_SYNTHESIZE(float, _cdTime, CDTime);
	void ClickCallBack(Ref* obj);
	void CoolDownCallBack(Node* node);

private:
	bool init(const char* Normal, const char* Click,
		const char* Mask, float CDTime);

	void CoolDownReduce(float dt);

private:
	MenuItemImage* _itemSkillButton;
	Sprite* _Mask;
	ProgressTimer* _ProgressTimer;
	float CdTime;
};