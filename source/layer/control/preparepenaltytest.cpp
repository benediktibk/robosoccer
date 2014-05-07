#include "layer/control/preparepenaltytest.h"
#include "layer/control/preparepenalty.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/control/userinputfetchermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

void PreparePenaltyTest::tearDown()
{
	RoboSoccerStateTest::tearDown();
	m_userInputFetcherMock = 0;
}

RoboSoccerState *PreparePenaltyTest::createInstance()
{
	m_userInputFetcherMock = new UserInputFetcherMock();
	return new PreparePenalty(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher, m_userInputFetcherMock);
}

void PreparePenaltyTest::nextState_executePenaltyButNoSelection_0()
{
	m_userInputFetcherMock->setSelectionMade(false);
	m_referee->setExecutePenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PreparePenaltyTest::nextState_hasPenalty_preparePenaltyOffensive()
{
	m_userInputFetcherMock->setSelectionMade(true);
	m_userInputFetcherMock->setPlayOffensive(true);

	State *state = m_state->nextState();

	PreparePenaltyOffensive *stateCasted = dynamic_cast<PreparePenaltyOffensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PreparePenaltyTest::nextState_hasNotPenalty_preparePenaltyDefensive()
{
	m_userInputFetcherMock->setSelectionMade(true);
	m_userInputFetcherMock->setPlayOffensive(false);

	State *state = m_state->nextState();

	PreparePenaltyDefensive *stateCasted = dynamic_cast<PreparePenaltyDefensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PreparePenaltyTest::update_empty_oneCallToUpdateUserInputFetcher()
{
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_userInputFetcherMock->getCallsToUpdate());
}
