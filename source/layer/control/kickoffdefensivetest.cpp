#include "layer/control/kickoffdefensivetest.h"
#include "layer/control/kickoffdefensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *KickOffDefensiveTest::createInstance()
{
	return new KickOffDefensive(*m_logger, *m_referee);
}