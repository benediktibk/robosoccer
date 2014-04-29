#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/storage.h"
#include "layer/autonomous/robotimpl.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

Team::Team(Storage &storage) :
	m_goalie(new RobotImpl(storage.getOwnRobot(0))),
	m_player1(new RobotImpl(storage.getOwnRobot(1))),
	m_player2(new RobotImpl(storage.getOwnRobot(2)))
{ }

Robot& Team::getGoalie() const
{
	return *m_goalie;
}

Robot& Team::getPlayerCloseToBall(const IntelligentBall &/*ball*/) const
{
	return *m_player1;
}

Robot &Team::getRobotByNumber(unsigned int i)
{
	switch(i)
	{
	case 0:
		return *m_goalie;
	case 1:
		return *m_player1;
	case 2:
		return *m_player2;
	default:
		assert(false);
	}

	// avoid errors from the compiler
	return *m_goalie;
}