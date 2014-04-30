#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/storage.h"
#include "layer/autonomous/robotimpl.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

TeamImpl::TeamImpl(Storage &storage) :
	m_goalie(new RobotImpl(storage.getOwnRobot(0))),
	m_fieldPlayerOne(new RobotImpl(storage.getOwnRobot(1))),
	m_fieldPlayerTwo(new RobotImpl(storage.getOwnRobot(2)))
{ }

TeamImpl::~TeamImpl()
{
	delete m_goalie;
	m_goalie = 0;
	delete m_fieldPlayerOne;
	m_fieldPlayerOne = 0;
	delete m_fieldPlayerTwo;
	m_fieldPlayerTwo = 0;
}

Robot& TeamImpl::getGoalie()
{
	return *m_goalie;
}

Robot& TeamImpl::getPlayerCloserToBall(const IntelligentBall &/*ball*/)
{
	return *m_fieldPlayerOne;
}

Robot &TeamImpl::getFirstFieldPlayer()
{
	return *m_fieldPlayerOne;
}

Robot &TeamImpl::getSecondFieldPlayer()
{
	return *m_fieldPlayerTwo;
}

Robot &TeamImpl::getRobotByNumber(unsigned int i)
{
	switch(i)
	{
	case 0:
		return *m_goalie;
	case 1:
		return *m_fieldPlayerOne;
	case 2:
		return *m_fieldPlayerTwo;
	default:
		assert(false);
	}

	// avoid errors from the compiler
	return *m_goalie;
}
