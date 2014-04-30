#include "layer/control/pausetest.h"
#include "layer/control/pause.h"
#include "layer/control/preparekickoff.h"
#include "layer/control/preparepenalty.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/storagemock.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PauseTest::createInstance()
{
	return new Pause(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void PauseTest::nextState_prepareKickOffSet_prepareKickOff()
{
	m_referee->setPrepareForKickOff(true);

	State *state = m_state->nextState();

	PrepareKickOff *stateCasted = dynamic_cast<PrepareKickOff*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PauseTest::nextState_gamePaused_0()
{
	m_referee->setGamePaused(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PauseTest::nextState_preparePenaltySet_preparePenalty()
{
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	PreparePenalty *stateCasted = dynamic_cast<PreparePenalty*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PauseTest::nextState_continuePlayingSet_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PauseTest::update_mockRobots_allRobotsGotOneCallToStop()
{
	m_state->update();

	for (unsigned int i = 0; i < 3; ++i)
	{
		Robot &robot = m_ownTeam->getRobotByNumber(i);
		robot.update();
	}

	ControllableRobotMock const &robot = m_storage->getOwnRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, robot.getCallsToStop());
}