#include "layer/control/preparepenaltytest.h"
#include "layer/control/preparepenalty.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;

RoboSoccerState *PreparePenaltyTest::createInstance()
{
	return new PreparePenalty(*m_logger, *m_referee);
}
