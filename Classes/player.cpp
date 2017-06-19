#include "player.h"
#include "MapLayer.h"

Player::Player() :avail(true)
{
}

Player::~Player()
{
}

//create the player sprite on the map
Player * Player::createWithMap(MapLayer * layer)
{
	Player *pRet = new Player();
	
	if (pRet && pRet->initWithLayer(layer)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

//initialize the player
bool Player::initWithLayer(MapLayer * layer)
{
	bool bRet = false;

	do
	{
		this->initWithFile("Player.png");
		m_layer = layer;
		bRet = true;
	} while (0);

	return bRet;
}

//use the A* way-finding algorithm to find the shorest way
void Player::moveToward(Point & pos)
{
	//this->setAvail(false);
	auto currPosition = this->getPosition();
	auto fromPos = m_layer->tileCoordForPosition(currPosition);
	auto toPos = m_layer->tileCoordForPosition(pos);

	//if the current position is equal to the target position, do nothing.
	if (fromPos == toPos)
	{
		return;
	}

	//if the target tile isn't valid or is a barrier tile, do nothing
	if (!m_layer->isValidTileCoord(toPos) || m_layer->isBarrierTile(toPos))
	{
		this->setAvail(true);
		return;
	}

	//clear the open list and close list
	m_spOpen.clear();
	m_spClose.clear();

	//add the player position to the open coord list
	this->insertInOpenSteps(ShortestPathStep::createWithPos(fromPos));
	
	//when the size of the open list isn't empty, do
	//realize the A* way-finding algorithm
	//the F value means the sum of the H value and the G value
	//the G value is the number
	do
	{
		//get the current step on the begin of the open list
		ShortestPathStep *currStep = m_spOpen.at(0);

		//push back the current step to the open list
		m_spClose.pushBack(currStep);
		//erase the beginning step in the open list
		m_spOpen.erase(0);

		//if current step is the target tile, player starts moving to the target position
		if (currStep->getPosition() == toPos)
		{
			
			this->constructPathAndStartAnimFromStep(currStep);
			
			//clear the lists
			m_spOpen.clear();
			m_spClose.clear();
			
			//break
			break;
		}

		//get the adjacent walkable tile coords array
		PointArray * adjSteps = m_layer->walkableAdjacentTileCoord(currStep->getPosition());

		//check for the lowest F value of each tile in the adjacent walkable tile coords array
		for (size_t i = 0; i < adjSteps->count(); ++i)
		{
			ShortestPathStep * step = ShortestPathStep::createWithPos(adjSteps->getControlPointAtIndex(i));
			//check if the step is in the close list, if so, check the next 
			if (this->getStepIndex(m_spClose, step) != -1)
			{
				continue;
			}

			//get move cost to move from current step to the adjStep
			int moveCost = this->costToMoveFromStepToAdjacentStep(currStep, step);
			//get the step position in the open list
			size_t index = this->getStepIndex(m_spOpen, step);

			if (index == -1) //the step isn't in the open list
			{
				//set the current step as the parent step of the step
				step->setParent(currStep);
				//set the G and H value
				step->setGScore(currStep->getGScore() + moveCost);
				step->setHScore(this->computeHScoreFromCoordToCoord(step->getPosition(), toPos));
				//insert the step into open steps list
				this->insertInOpenSteps(step);
			}
			else
			{
				//compare the index step's G score with the step's G score
				step = m_spOpen.at(index);
				if ((currStep->getGScore() + moveCost) < step->getGScore())
				{
					//set the G score of the index step
					step->setGScore(currStep->getGScore() + moveCost);

					//retain the step
					step->retain();

					// erase it from the open list
					m_spOpen.erase(index);
					//add it into the open step
					this->insertInOpenSteps(step);
					step->release();
				}
			}
		}

	} while (m_spOpen.size() > 0);
}

void Player::insertInOpenSteps(Player::ShortestPathStep * pPath)
{
	//get the F score of the pPath step
	int stepFScore = pPath->getFScore();
	size_t count = m_spOpen.size();
	size_t i = 0;

	//get the position to insert it
	for (; i < count; ++i)
	{
		if (stepFScore <= m_spOpen.at(i)->getFScore())
		{
			break;
		}
	}
	m_spOpen.insert(i, pPath);
}

//compute the H score, the cost from current coord to the target
int Player::computeHScoreFromCoordToCoord(const Point &fromCoord, const Point &toCoord)
{
	//ignore the barrier
	return abs(toCoord.x - fromCoord.x) + abs(toCoord.y - fromCoord.y);
}

int Player::costToMoveFromStepToAdjacentStep(const Player::ShortestPathStep *fromStep, const Player::ShortestPathStep *toStep) 
{
	return 1;
}

//get the position of the step in the steps vector
size_t Player::getStepIndex(cocos2d::Vector<Player::ShortestPathStep*>& steps, Player::ShortestPathStep * step)
{
	for (size_t i = 0; i < steps.size(); ++i)
	{
		if (steps.at(i)->isEqual(step))
		{
			return i;
		}
	}

	return -1;
}

//get the shorest path and the point array of path
void Player::constructPathAndStartAnimFromStep(Player::ShortestPathStep * step)
{
	m_shortestPath.clear();

	do
	{
		if (step->getParent())
		{
			m_shortestPath.insert(0, step);
		}
		step = step->getParent();
	} while (step);

	this->popStepAndAnim();
}

//move and animation
void Player::popStepAndAnim()
{
	auto currPosOfPlayer = this->getPosition();
	auto currTileCoordPos = m_layer->tileCoordForPosition(currPosOfPlayer);

	if (m_shortestPath.size() == 0)
	{
		return;
	}

	ShortestPathStep *s = m_shortestPath.at(0);

	MoveTo *moveAction = MoveTo::create(0.25f, m_layer->positionForTileCoord(s->getPosition()));
	
	CallFunc *moveCallBack = CallFunc::create(CC_CALLBACK_0(Player::popStepAndAnim, this));

	if (m_layer->isFoodTile(currTileCoordPos))
	{
		m_layer->removeTheFood(currTileCoordPos);
	}

	m_shortestPath.erase(0);

	if (m_shortestPath.size() == 0)
	{
		this->runAction(Sequence::create(moveAction,CallFunc::create(CC_CALLBACK_0(Player::changeAvail,this)),nullptr));

		return;
	}

	this->runAction(Sequence::create(moveAction, moveCallBack, nullptr));
}

void Player::changeAvail()
{
	CCLOG("changeAvail");
	this->setAvail(true);
	return;
}
Player::ShortestPathStep::ShortestPathStep() :
	m_Position(Point::ZERO),
	m_GScore(0),
	m_HScore(0),
	m_parent(nullptr)
{
}

Player::ShortestPathStep::~ShortestPathStep()
{
}

Player::ShortestPathStep * Player::ShortestPathStep::createWithPos(const Point & pos)
{
	ShortestPathStep *pPath = new ShortestPathStep();
	if (pPath && pPath->initWithPos(pos))
	{
		pPath->autorelease();
		return pPath;
	}
	else
	{
		CC_SAFE_DELETE(pPath);
		return nullptr;
	}
}

bool Player::ShortestPathStep::initWithPos(const Point & pos)
{
	bool bRet = false;

	do
	{
		this->setPosition(pos);
		bRet = true;
	} while (0);
	
	return bRet;
}

int Player::ShortestPathStep::getFScore() const
{
	return this->getGScore() + this->getHScore();
}

bool Player::ShortestPathStep::isEqual(const ShortestPathStep * pPath) const
{
	return this->getPosition() == pPath->getPosition();
}
