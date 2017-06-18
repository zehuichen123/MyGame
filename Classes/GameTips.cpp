#include "GameTips.h"
GameTipsSprite::GameTipsSprite() 
{}
GameTipsSprite::~GameTipsSprite() 
{}
bool GameTipsSprite::init() {
	bool ret = false;
	do {
		CC_BREAK_IF(!Node::init());
		CC_BREAK_IF(!setUpdateView());
		ret = true;
	} while (0);
	return ret;
}

bool GameTipsSprite::setUpdateView() {
	bool ret = false;
	do {
		//goldIcon
		auto gold = Sprite::create("game/coin.png");
		CC_BREAK_IF(!gold);
		gold->setPosition(Point::ZERO-Point(5,0));
		this->addChild(gold);

		//total gold number
		auto goldnumber = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!goldnumber);
		goldnumber->setAnchorPoint(Point(0, 0.5));
		goldnumber->setPosition(Point(gold->getContentSize().width / 2, 0));
		this->addChild(goldnumber, 1, 1);

		//the current stage of monster
		auto monstnumber = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!monstnumber);
		monstnumber->setAnchorPoint(Point(0, 0.5));
		monstnumber->setPosition(Point(goldnumber->boundingBox().getMaxX() + 120, 0));
		this->addChild(monstnumber, 1, 2);

		auto monstlable = LabelTTF::create("/", "Arial", 24);
		CC_BREAK_IF(!monstlable);
		monstlable->setAnchorPoint(Point(0, 0.5));
		monstlable->setPosition(Point(monstnumber->boundingBox().getMaxX() + 10, 0));
		monstlable->setColor(ccc3(255, 255, 255));
		this->addChild(monstlable, 1);

		// the total stage of the monster
		auto monsttotalnumber = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!monsttotalnumber);
		monsttotalnumber->setAnchorPoint(Point(0, 0.5));
		monsttotalnumber->setPosition(Point(monstlable->boundingBox().getMaxX(), 0));
		this->addChild(monsttotalnumber, 1, 3);

		//show the stage word:"stage"
		auto stagelable =LabelTTF::create("Stage:", "Arial",24);
		CC_BREAK_IF(!stagelable);
		stagelable->setAnchorPoint(Point(0, 0.5));
		stagelable->setPosition(Point(monsttotalnumber->boundingBox().getMaxX() + 40, 0));
		stagelable->setColor(ccc3(255, 255, 255));
		this->addChild(stagelable, 1);

		auto stagenumber = LabelAtlas::create("0", "game/numWhite.png", 25, 45, '0');
		CC_BREAK_IF(!stagenumber);
		stagenumber->setAnchorPoint(Point(0, 0.5));
		stagenumber->setPosition(Point(stagelable->boundingBox().getMaxX(), 0));
		this->addChild(stagenumber, 1, 4);

		ret = true;
	} while (0);
	return ret;
}

void GameTipsSprite::setgoldNum(int num) {
	auto goldnumber = (LabelAtlas*) this->getChildByTag(1);
	char* temp = new char[12];
	sprintf(temp, "%d", num);
	goldnumber->setString(temp);
	delete temp;
}
void GameTipsSprite::setMonstNum(int num) {
	auto monstnumber = (LabelAtlas*) this->getChildByTag(2);
	char* temp = new char[12];
	sprintf(temp, "%d", num);
	monstnumber->setString(temp);
	delete temp;
}
void GameTipsSprite::setMonstTotalNum(int num) {
	auto monsttotalnumber = (LabelAtlas*) this->getChildByTag(3);
	char* temp = new char[12];
	sprintf(temp, "%d", num);
	monsttotalnumber->setString(temp);
	delete temp;
}
void GameTipsSprite::setStageNum(int num) {
	auto stagenumber = (LabelAtlas*) this->getChildByTag(4);
	char* temp = new char[12];
	sprintf(temp, "%d", num);
	stagenumber->setString(temp);
	delete temp;
}



