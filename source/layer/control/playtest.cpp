#include "layer/control/playtest.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PlayTest::createInstance()
{
	return new Play(*m_logger, *m_referee);
}
