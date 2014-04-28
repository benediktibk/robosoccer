#include "layer/control/robosoccerstatetest.h"
#include "layer/control/robosoccerstate.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;

void RoboSoccerStateTest::setUp()
{
	m_referee = new RefereeMock();
	m_logger = new LoggerMock();
	m_state = createInstance();
}

void RoboSoccerStateTest::tearDown()
{
	delete m_state;
	m_state = 0;
	delete m_referee;
	m_referee = 0;
	delete m_logger;
	m_logger = 0;
}
