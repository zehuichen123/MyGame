#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);
Global::Global() {};
Global::~Global()
{
	CC_SAFE_DELETE(gameLayer);
	CC_SAFE_DELETE(operateLayer);
	CC_SAFE_DELETE(stateLayer);
	CC_SAFE_DELETE(hero);
	gameLayer = NULL;
	operateLayer = NULL;
	stateLayer = NULL;
	hero = NULL;
	tileMap = NULL;
}
