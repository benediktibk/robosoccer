#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/storage.h"
#include "layer/autonomous/robotimpl.h"

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

