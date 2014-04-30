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

void IntelligentBallTest::isMoving_movingFast_true()
{
	m_ballMock->setVelocity(5);

	CPPUNIT_ASSERT(m_intelligentBall->isMoving());
}

void IntelligentBallTest::isMoving_notMoving_false()
{
	m_ballMock->setVelocity(0);

	CPPUNIT_ASSERT(!m_intelligentBall->isMoving());
}
