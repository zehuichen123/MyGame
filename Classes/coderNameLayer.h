//this is a layer to show 
//the name of all developers' name
//with a return button and a pic

#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "welcomeLayer.h"
USING_NS_CC;
class coderNameLayer :public BaseLayer {
public:
	coderNameLayer();
	~coderNameLayer();
	static Scene* createScene();
	virtual bool init();
	bool setUpdateView();
	CREATE_FUNC(coderNameLayer);
private:
	void MenuCallBack(Ref* pSender);
};