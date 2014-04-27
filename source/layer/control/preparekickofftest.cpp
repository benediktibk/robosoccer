#include "layer/control/preparekickofftest.h"
#include "layer/control/preparekickoff.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PrepareKickOffTest::createInstance()
{
	return new PrepareKickOff(*m_logger, *m_referee);
}
