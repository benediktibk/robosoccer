#include "layer/control/penaltyoffensivetest.h"
#include "layer/control/penaltyoffensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PenaltyOffensiveTest::createInstance()
{
	return new PenaltyOffensive(*m_logger, *m_referee);
}