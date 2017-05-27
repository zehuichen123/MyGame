#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
HelloWorld::HelloWorld(){}
HelloWorld::~HelloWorld(){}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("TestUI.ExportJson");
	//this->addChild(UI);
	auto m_pUILayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("DemoLogin.ExportJson");
	this->addChild(m_pUILayer);
	Button* close_button = (Button*)Helper::seekWidgetByName(m_pUILayer, "close_Button");
	close_button->addTouchEventListener(this, toucheventselector(HelloWorld::menuCloseCallback));
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender, TouchEventType type)
{
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

