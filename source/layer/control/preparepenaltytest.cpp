#include "layer/control/preparepenaltytest.h"
#include "layer/control/preparepenalty.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PreparePenaltyTest::createInstance()
{
	return new PreparePenalty(*m_logger, *m_referee);
}

void PreparePenaltyTest::nextState_executePenalty_prepareState()
{
	m_referee->setExecutePenalty(true);

	State *state = m_state->nextState();

	PreparePenaltyDefensive *stateDefensive = dynamic_cast<PreparePenaltyDefensive*>(state);
	PreparePenaltyOffensive *stateOffensive = dynamic_cast<PreparePenaltyOffensive*>(state);
	CPPUNIT_ASSERT(stateDefensive != 0 || stateOffensive != 0);
}

void PreparePenaltyTest::nextState_hasPenalty_preparePenaltyOffensive()
{
	m_referee->setHasKickOffOrPenalty(true);

	State *state = m_state->nextState();

	PreparePenaltyOffensive *stateCasted = dynamic_cast<PreparePenaltyOffensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void PreparePenaltyTest::nextState_hasNotPenalty_preparePenaltyDefensive()
{
	m_referee->setHasKickOffOrPenalty(false);

	State *state = m_state->nextState();

	PreparePenaltyDefensive *stateCasted = dynamic_cast<PreparePenaltyDefensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}
