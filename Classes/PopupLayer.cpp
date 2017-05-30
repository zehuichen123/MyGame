#include "PopupLayer.h"
PopupLayer::PopupLayer()
{
}
PopupLayer::~PopupLayer()
{
}

bool PopupLayer::init(Layer* target)
{
	if (!Layer::init())
	{
		return false;
	}
	addChild(BarrierLayer::create(), 0);
	addChild(target, 1);
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
	auto  act1 = MoveTo::create(0.0f, Vec2(0, WinSize.height));
	auto  act2 = MoveTo::create(0.5f, Vec2::ZERO);
	return Sequence::createWithTwoActions(act1, act2);

}