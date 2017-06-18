#include "Enemy.h"
Enemy::Enemy()
{
}
Enemy::~Enemy()
{}
bool Enemy::setUpdateView()
{
	bool ret = false;
	do {
		

		auto bloodbg = Sprite::create("game/monster_blood_frame.png");
		bloodbg->setPosition(this->getContentSize().width/2,this->getContentSize().height+2);
		this->addChild(bloodbg,1);


		bloodValue = ProgressTimer::create(Sprite::create("game/monster_blood.png"));
		CC_BREAK_IF(!bloodValue);
		bloodValue->setType(ProgressTimer::Type::BAR);
		bloodValue->setMidpoint(Point(0, 0.5));
		bloodValue->setBarChangeRate(Point(1, 0));
		bloodValue->setPercentage(100);
		bloodValue->setPosition(bloodbg->getContentSize()/2);
		bloodbg->addChild(bloodValue);

		
		ret = true;
	} while (0);
	return ret;
}
bool Enemy::init()
{
	bool ret = false;
	do {

		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monster/dutu.plist","monster/dutu.png");
		this->initWithSpriteFrameName("dutu-10.png");

		Animation *walkAnim = this->createNormalAnimation("dutu-1%d.png", 8, 8);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		Animation *attackAnim = this->createNormalAnimation("dutu-2%d.png", 8, 8);
		this->setNormalAttackAction(RepeatForever::create(Animate::create(attackAnim)));

		Animation *deadAnim = this->createNormalAnimation("dutu-3%d.png", 8, 8);
		this->setDeadAction(Sequence::create(
						Animate::create(deadAnim),
						Blink::create(3, 9),
						CallFuncN::create(CC_CALLBACK_1(Enemy::deadCallBackAction, this)), NULL));
		//this->runAction(this->getDeadAction());

		CC_BREAK_IF(!Enemy::setUpdateView());

		this->scheduleUpdate();
		ret = true;
	} while (0);

	return ret;
}
void Enemy::runNormalAttackAction()
{
	this->runAction(this->getNormalAttackAction());
	this->schedule(schedule_selector(Enemy::attackCallBackAction),1, 20, 0);
	
}
void Enemy::attackCallBackAction(float dt)
{
	auto hurt = this->getDamageStrength();
	auto citySprite = global->GcityBloodSprite;
	citySprite->cityBloodSprite::beAttack(hurt);
}

void Enemy::runDeadAction()
{
	this->stopAllActions();
	this->runAction(this->getDeadAction());
	auto gameTipsSprite = global->GgameTipsSprite;
	int goldnum = UserDefault::sharedUserDefault()->getIntegerForKey("goldNum", 0);
	goldnum = 1 + goldnum;
	UserDefault::sharedUserDefault()->setIntegerForKey("goldNum", goldnum);
	gameTipsSprite->setgoldNum(goldnum);

	int killtemp = UserDefault::sharedUserDefault()->getIntegerForKey("killtemp", 1);
	UserDefault::sharedUserDefault()->setIntegerForKey("killtemp", killtemp + 1);
}

void Enemy::deadCallBackAction(Node* pSender)
{
	this->setVisible(false);
	global->GdefenderGameLayer->removeChild(this, true);
}
void Enemy::runWalkAction()
{
	this->runAction(this->getWalkAction());
}

bool Enemy::beAttacked()
{
	float hurt = getWeaponHurt();
	float currtLife = this->getcurLifeValue();
	float currtDefence = this->getDefense();
	currtLife = currtLife - hurt*(1 - currtDefence);
	this->setcurLifeValue(currtLife);
	if (currtLife <= 0)						//judge the enemy is dead ?false:false:true
	{
		bloodValue->setPercentage(0);
		this->runDeadAction();
		return false;
	}
	else
	bloodValue->setPercentage(currtLife / this->getLifeValue()*100);
	return true;
}

bool Enemy::beSkillAttack()
{
	float hurt = getSkillHurt();
	float currtLife = this->getcurLifeValue();
	float currtDefence = this->getDefense();
	currtLife = currtLife - hurt*(1 - currtDefence);
	this->setcurLifeValue(currtLife);
	if (currtLife <= 0)						//when the current value<0,enemy run dead action
	{
		bloodValue->setPercentage(0);
		this->runDeadAction();
		return false;
	}
	else									//set the enemy 's currt life value to the life value Bar
		bloodValue->setPercentage(currtLife / this->getLifeValue() * 100);
	return true;
}

void Enemy::Move()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Determine where to spawn the this along the Y axis
	int minY = this->getContentSize().height;
	int maxY = visibleSize.height - this->getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (CCRANDOM_0_1() * rangeY) + minY;
	this->setPosition(Point(visibleSize.width + this->getContentSize().width / 2, actualY));
	
	auto actionMove = MoveTo::create(visibleSize.width/speed,
								Point(visibleSize.width * 3 / 16, actualY));
	auto actionAttack = this->getNormalAttackAction();
	auto actionWalk = this->getWalkAction();
	auto actionMoveDone = CallFuncN::create(
		CC_CALLBACK_1(Enemy::monsterMoveFinished, this));

	this->runWalkAction();
	this->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

/* when the enemy reach the destination,begin to attck the citySprite */
void Enemy::monsterMoveFinished(Ref* pSender)
{
	this->stopAllActions();
	this->runNormalAttackAction();
}

/*update the enemy's current life value*/
void Enemy::update(float dt)
{
	bloodValue->setPercentage((float)this->getcurLifeValue() / this->getLifeValue() * 100);
}

