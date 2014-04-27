#include "layer/control/preparepenaltydefensivetest.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PreparePenaltyDefensiveTest::createInstance()
{
	return new PreparePenaltyDefensive(*m_logger, *m_referee);
}