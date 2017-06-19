#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MapLayer;

class Player : public Sprite
{
public:
	Player();
	~Player();

	bool initWithLayer(MapLayer * layer);
	static Player * createWithMap(MapLayer * layer);
	void moveToward(Point & pos);
	CC_SYNTHESIZE(bool, avail, Avail);
	CREATE_FUNC(Player);

	class ShortestPathStep : public Ref
	{
	public:
		ShortestPathStep();
		~ShortestPathStep();
		static ShortestPathStep * createWithPos(const Point & pos);
		bool initWithPos(const Point & pos);
		int getFScore() const;
		bool isEqual(const ShortestPathStep * pPath) const;
		CC_SYNTHESIZE(Point, m_Position, Position);
		CC_SYNTHESIZE(int, m_GScore, GScore);
		CC_SYNTHESIZE(int, m_HScore, HScore);
		CC_SYNTHESIZE(ShortestPathStep*, m_parent, Parent);
	};

	void insertInOpenSteps(Player::ShortestPathStep * pPath);
	int computeHScoreFromCoordToCoord(const Point & fromCoord, const Point & toCoord);
	int costToMoveFromStepToAdjacentStep(const Player::ShortestPathStep * fromStep, const Player::ShortestPathStep * toStep);
	size_t getStepIndex( cocos2d::Vector<Player::ShortestPathStep*> &steps, Player::ShortestPathStep *step);
	void constructPathAndStartAnimFromStep(Player::ShortestPathStep *step);
	void popStepAndAnim();
	void changeAvail();
private:
	MapLayer * m_layer;
	cocos2d::Vector<ShortestPathStep*> m_spOpen;
	cocos2d::Vector<ShortestPathStep*> m_spClose;
	cocos2d::Vector<ShortestPathStep*> m_shortestPath;
};

#endif // !_PLAYER_H_
