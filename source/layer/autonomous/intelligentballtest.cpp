#include "layer/autonomous/intelligentballtest.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ballmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

void IntelligentBallTest::setUp()
{
	m_ballMock = new BallMock();
	m_intelligentBall = new IntelligentBallImpl(*m_ballMock);
}

void IntelligentBallTest::tearDown()
{
	delete m_intelligentBall;
	m_intelligentBall = 0;
	delete m_ballMock;
	m_ballMock = 0;
}
