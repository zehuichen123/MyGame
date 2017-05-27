#include "GameScene.h"
GameScene::GameScene(){}
GameScene::~GameScene(){}
Scene* GameScene::createScene()
{
	auto gameScene = Scene::create();

	auto gameLayer = GameLayer::create();
	gameScene->addChild(gameLayer,0);

	auto operateLayer = OperateLayer::create();
	gameScene->addChild(operateLayer,1);

	auto stateLayer = StateLayer::create();
	gameScene->addChild(stateLayer,2);

	auto buttonLayer = ButtonLayer::create();
	gameScene->addChild(buttonLayer,3);

	return gameScene;
}