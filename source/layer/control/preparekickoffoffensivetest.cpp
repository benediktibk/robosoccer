#include "layer/control/preparekickoffoffensivetest.h"
#include "layer/control/preparekickoffoffensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PrepareKickOffOffensiveTest::createInstance()
{
	return new PrepareKickOffOffensive(*m_logger, *m_referee);
}