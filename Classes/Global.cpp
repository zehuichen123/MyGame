#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);
Global::Global() {};
Global::~Global()
{
	CC_SAFE_DELETE(gameLayer);
	CC_SAFE_DELETE(operateLayer);
	CC_SAFE_DELETE(stateLayer);
	gameLayer = NULL;
	operateLayer = NULL;
	stateLayer = NULL;
	tileMap = NULL;
}
