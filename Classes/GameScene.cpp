#include "GameScene.h"
Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto gameLayer = GameLayer::create();
	scene->addChild(gameLayer, 0);

	auto operateLayer = OperateLayer::create();
	scene->addChild(operateLayer, 1);

	auto stateLayer = StateLayer::create();
	scene->addChild(stateLayer, 2);

	auto button = ButtonLayer::create();
	scene->addChild(button, 3);
	return scene;
}