#include "layer/control/penaltydefensivetest.h"
#include "layer/control/penaltydefensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PenaltyDefensiveTest::createInstance()
{
	return new PenaltyDefensive(*m_logger, *m_referee);
}