#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/storage.h"
#include "layer/autonomous/robotimpl.h"
#include "common/geometry/pose.h"
#include <assert.h>
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

TeamImpl::TeamImpl(Storage &storage, const Watch &watch, Logger &logger) :
	m_goalie(new RobotImpl(storage.getOwnRobot(0), watch, logger)),
	m_fieldPlayerOne(new RobotImpl(storage.getOwnRobot(1), watch, logger)),
	m_fieldPlayerTwo(new RobotImpl(storage.getOwnRobot(2), watch, logger))
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

Robot& TeamImpl::getPlayerCloserToBall(const IntelligentBall &ball)
{
	if(m_fieldPlayerOne->getCurrentPose().getPosition().distanceTo(ball.getPosition()) <
			m_fieldPlayerTwo->getCurrentPose().getPosition().distanceTo(ball.getPosition()))
		return *m_fieldPlayerOne;
	else
		return *m_fieldPlayerTwo;
}

Robot &TeamImpl::getPlayerFartherAwayFromBall(const IntelligentBall &ball)
{
	if(m_fieldPlayerOne->getCurrentPose().getPosition().distanceTo(ball.getPosition()) <
			m_fieldPlayerTwo->getCurrentPose().getPosition().distanceTo(ball.getPosition()))
		return *m_fieldPlayerTwo;
	else
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

std::vector<Circle> TeamImpl::getObstacles()
{
	vector<Circle> obstacles;
	obstacles.reserve(3);

	for(unsigned int i=0;i<3;i++)
		obstacles.push_back(getRobotByNumber(i).getObstacle());

	return obstacles;
}
