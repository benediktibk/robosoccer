#include "layer/control/preparekickoffdefensivetest.h"
#include "layer/control/preparekickoffdefensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PrepareKickOffDefensiveTest::createInstance()
{
	return new PrepareKickOffDefensive(*m_logger, *m_referee);
}