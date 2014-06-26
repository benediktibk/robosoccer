#include "layer/control/playtest.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "common/logging/loggermock.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Common::Geometry;

RoboSoccerState *PlayTest::createInstance()
{
	return new Play(
				*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball,
				*m_targetPositionFetcher, *m_fieldPositionCheckerGoalKeeper);
}

void PlayTest::nextState_everythingSet_0()
{
	m_referee->setContinuePlaying(true);
	m_referee->setExecuteKickOff(true);
	m_referee->setExecutePenalty(true);
	m_referee->setPrepareForKickOff(true);
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PlayTest::nextState_notContinuePlaying_pause()
{
	m_referee->setContinuePlaying(false);
	m_referee->setExecuteKickOff(true);
	m_referee->setExecutePenalty(true);
	m_referee->setPrepareForKickOff(true);
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PlayTest::update_ballInDangerZone_goalieGotCallToStop()
{
	m_ball->setIsMoving(false);
	m_ball->setPosition(Point(-1.44, 0.03));

	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, robot.getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToStop());
}
