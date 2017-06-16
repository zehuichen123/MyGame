#include "BarrierLayer.h"
BarrierLayer::BarrierLayer()
{
}
BarrierLayer::~BarrierLayer()
{
}
bool BarrierLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
	this->addChild(backLayerColor);

	auto callBack = [](Touch*, Event*)
	{
		return true;
	};
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callBack;
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}