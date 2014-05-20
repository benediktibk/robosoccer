#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/storage.h"
#include "layer/autonomous/robotimpl.h"
#include "common/geometry/pose.h"
#include <assert.h>
#include "common/geometry/circle.h"
#include "common/routing/routerimpl.h"
#include "layer/main/fieldpositioncheckerfieldplayer.h"
#include "layer/main/fieldpositioncheckergoalkeeper.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Layer::Main;
using namespace std;

TeamImpl::TeamImpl(Storage &storage, const Watch &watch, Logger &logger,
				   FieldPositionCheckerGoalkeeper &fieldPositionCheckerGoalkeeper,
				   FieldPositionCheckerFieldPlayer &fieldPositionCheckerFieldPlayer, ObstacleFetcher &obstacleFetcher) :
	m_routerGoalie(new RouterImpl(ReadableRobot::getWidth(), fieldPositionCheckerGoalkeeper)),
	m_routerFieldPlayer(new RouterImpl(ReadableRobot::getWidth(), fieldPositionCheckerFieldPlayer)),
	m_goalie(new RobotImpl(storage.getOwnRobot(0), *m_routerGoalie, watch, logger, 0, obstacleFetcher)),
	m_fieldPlayerOne(new RobotImpl(storage.getOwnRobot(1), *m_routerFieldPlayer, watch, logger, 1, obstacleFetcher)),
	m_fieldPlayerTwo(new RobotImpl(storage.getOwnRobot(2), *m_routerFieldPlayer, watch, logger, 2, obstacleFetcher))
{ }

TeamImpl::~TeamImpl()
{
	delete m_goalie;
	m_goalie = 0;
	delete m_fieldPlayerOne;
	m_fieldPlayerOne = 0;
	delete m_fieldPlayerTwo;
	m_fieldPlayerTwo = 0;
	delete m_routerGoalie;
	m_routerGoalie = 0;
	delete m_routerFieldPlayer;
	m_routerFieldPlayer = 0;
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
