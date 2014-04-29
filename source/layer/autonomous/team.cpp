#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/storage.h"
#include "layer/autonomous/robotimpl.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

Team::Team(Storage &storage) :
	m_goalie(new RobotImpl(storage.getOwnRobot(0))),
	m_fieldPlayerOne(new RobotImpl(storage.getOwnRobot(1))),
	m_fieldPlayerTwo(new RobotImpl(storage.getOwnRobot(2)))
{ }

Robot& Team::getGoalie()
{
	return *m_goalie;
}

Robot& Team::getPlayerCloserToBall(const IntelligentBall &/*ball*/)
{
	return *m_fieldPlayerOne;
}

Robot &Team::getFirstFieldPlayer()
{
	return *m_fieldPlayerOne;
}

Robot &Team::getSecondFieldPlayer()
{
	return *m_fieldPlayerTwo;
}

Robot &Team::getRobotByNumber(unsigned int i)
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