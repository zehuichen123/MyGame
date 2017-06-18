#include "BarrierLayer.h"
BarrierLayer::BarrierLayer()
{}
BarrierLayer::~BarrierLayer()
{}

bool BarrierLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//set the barrierLayer's color :gray
	LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
	this->addChild(backLayerColor);

	auto callBack = [](Touch*, Event*)
	{
		return true;
	};
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callBack;
	listener->setSwallowTouches(true);					//the core of this layer's function
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}