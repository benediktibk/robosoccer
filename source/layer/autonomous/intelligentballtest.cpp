#include "layer/autonomous/intelligentballtest.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include "layer/abstraction/fieldside.h"
#include "common/geometry/compare.h"

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
	m_ballMock->setPosition(Point(5,5));

	CPPUNIT_ASSERT_EQUAL(Point(5,5), m_intelligentBall->getPosition());
}

void IntelligentBallTest::getRotation_shouldbe_1()
{
	Compare compare(0.001);
	m_ballMock->setRotation(Angle(1.0));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(1.0, m_intelligentBall->getRotation()));
}

void IntelligentBallTest::getMovingDirection_isLeft_Fieldsideleft()
{
	m_ballMock->setRotation(Angle(2.0));
	m_ballMock->setVelocity(5);

	CPPUNIT_ASSERT_EQUAL(m_intelligentBall->getMovingDirection(),FieldSideLeft);
}

void IntelligentBallTest::getMovingDirection_isRight_FielsideRight()
{
	m_ballMock->setRotation(Angle(0.0));
	m_ballMock->setVelocity(5);

	CPPUNIT_ASSERT_EQUAL(m_intelligentBall->getMovingDirection(),FieldSideRight);
}

void IntelligentBallTest::getCurrentFieldSide_isRight_FieldsideRight()
{
	m_ballMock->setPosition(Point(5.0,0.0));

	CPPUNIT_ASSERT_EQUAL(m_intelligentBall->getCurrentFieldSide(),FieldSideRight);
}

void IntelligentBallTest::getCurrentFieldSide_isLeft_FieldsideLeft()
{
	m_ballMock->setPosition(Point(-5.0,0.0));

	CPPUNIT_ASSERT_EQUAL(m_intelligentBall->getCurrentFieldSide(),FieldSideLeft);
}