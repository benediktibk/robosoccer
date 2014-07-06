#include "layer/control/kickoffoffensivetest.h"
#include "layer/control/kickoffoffensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/robotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::States;

RoboSoccerState *KickOffOffensiveTest::createInstance()
{
	return new KickOffOffensive(
				*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball,
				*m_targetPositionFetcher, *m_fieldPositionCheckerGoalKeeper);
}

void KickOffOffensiveTest::nextState_executeKickOff_0()
{
	m_referee->setExecuteKickOff(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void KickOffOffensiveTest::nextState_continuePlaying_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void KickOffOffensiveTest::nextState_notExecuteKickOffAndNotContinuePlaying_pause()
{
	m_referee->setContinuePlaying(false);
	m_referee->setExecuteKickOff(false);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void KickOffOffensiveTest::update_empty_oneRobotGotCallToKick()
{
	m_referee->setExecuteKickOff(true);

	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToKick());
}

void KickOffOffensiveTest::update_twiceCalled_onlyOneCallToKick()
{
	m_referee->setExecuteKickOff(true);

	m_state->update();
	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToKick());
}
