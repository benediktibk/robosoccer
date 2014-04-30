#include "layer/autonomous/intelligentballtest.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

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

void IntelligentBallTest::getPosition_shouldbe_5_5()
{
	Point shouldbe(5,5);
	m_ballMock->setBallPosition(shouldbe);

	Point is = m_intelligentBall->getPosition();
	double x = is.getX();
	double y = is.getY();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, x, 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, y, 0.00001);
}

void IntelligentBallTest::getRotation_shouldbe_1()
{
	Angle shouldbe(1.0);
	m_ballMock->setRotation(shouldbe);

	Angle is = m_intelligentBall->getRotation();
	double angle = is.getValueBetweenMinusPiAndPi();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, angle, 0.00001);
}
