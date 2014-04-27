#include "layer/control/preparepenaltyoffensivetest.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PreparePenaltyOffensiveTest::createInstance()
{
	return new PreparePenaltyOffensive(*m_logger, *m_referee);
}