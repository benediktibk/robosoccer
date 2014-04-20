#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/ballimpl.h"
#include "layer/abstraction/refereeimpl.h"
#include "layer/abstraction/readablerobotimpl.h"
#include "layer/abstraction/controllablerobotimpl.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

StorageImpl::StorageImpl() :
	m_ball(new BallImpl()),
	m_referee(new RefereeImpl())
{
	m_enemyRobots.reserve(3);
	m_enemyRobots.push_back(new ReadableRobotImpl());
	m_enemyRobots.push_back(new ReadableRobotImpl());
	m_enemyRobots.push_back(new ReadableRobotImpl());
	m_ownRobots.reserve(3);
	m_ownRobots.push_back(new ControllableRobotImpl());
	m_ownRobots.push_back(new ControllableRobotImpl());
	m_ownRobots.push_back(new ControllableRobotImpl());
}

StorageImpl::~StorageImpl()
{
	delete m_ball;
	m_ball = 0;
	delete m_referee;
	m_referee = 0;

	for (vector<ReadableRobot*>::iterator i = m_enemyRobots.begin(); i != m_enemyRobots.end(); ++i)
		delete *i;
	m_enemyRobots.clear();
	for (vector<ControllableRobot*>::iterator i = m_ownRobots.begin(); i != m_ownRobots.end(); ++i)
		delete *i;
	m_ownRobots.clear();
}

Ball &StorageImpl::getBall()
{
	return *m_ball;
}

ReadableRobot &StorageImpl::getEnemyRobot(unsigned int number)
{
	assert(number <= 2);
	return *(m_enemyRobots[number]);
}

ControllableRobot &StorageImpl::getOwnRobot(unsigned int number)
{
	assert(number <= 2);
	return *(m_ownRobots[number]);
}

Referee &StorageImpl::getReferee()
{
	return *m_referee;
}
