#include "layer/control/kickoffoffensivetest.h"
#include "layer/control/kickoffoffensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *KickOffOffensiveTest::createInstance()
{
	return new KickOffOffensive(*m_logger, *m_referee);
}