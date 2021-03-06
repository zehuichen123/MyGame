#include "PopupLayer.h"
PopupLayer::PopupLayer()
{}
PopupLayer::~PopupLayer()
{}

bool PopupLayer::init(Layer* target)
{
	if (!Layer::init())
	{
		return false;
	}
	this->addChild(BarrierLayer::create(), 0);
	this->addChild(target, 1);
	target->runAction(getAction());
	return true;
}

PopupLayer* PopupLayer::create(Layer* target)
{
	PopupLayer* popupLayer = new PopupLayer;
	if (popupLayer&&popupLayer->init(target))
	{
		popupLayer->autorelease();
		return popupLayer;
	}
	else
	{
		CC_SAFE_DELETE(popupLayer);
		return nullptr;
	}
}

Action* PopupLayer::getAction()
{
	Size WinSize = Director::getInstance()->getWinSize();
	auto  act1 = MoveTo::create(0.0f, Vec2(0, WinSize.height));	  //set the target layer's position at (0,winSize.height)
	auto  act2 = MoveTo::create(0.3f, Vec2::ZERO);

	return Sequence::create(act1, act2,CallFuncN::create(CC_CALLBACK_1(PopupLayer::pauseScene,this)),NULL);
}
void PopupLayer::pauseScene(Node* pSender)
{
	Director::getInstance()->pause();
}