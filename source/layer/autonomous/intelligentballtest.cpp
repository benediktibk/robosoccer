#include "layer/autonomous/intelligentballtest.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include "layer/abstraction/fieldside.h"
#include "common/geometry/compare.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "iostream"
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

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

void IntelligentBallTest::getObstacle_empty_sameAsFromBall()
{
	Circle obstacleShouldBe(Point(3, 4), 1);
	m_ballMock->setObstacle(obstacleShouldBe);

	Circle obstacle = m_intelligentBall->getObstacle();

	CPPUNIT_ASSERT_EQUAL(obstacleShouldBe, obstacle);
}

void IntelligentBallTest::getObstacles_empty_oneElementWhichIsSameAsFromBall()
{
	Circle obstacleShouldBe(Point(3, 4), 1);
	m_ballMock->setObstacle(obstacleShouldBe);

	vector<Circle> obstacles = m_intelligentBall->getObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	CPPUNIT_ASSERT_EQUAL(obstacleShouldBe, obstacles.front());
}

void IntelligentBallTest::getCurrentFieldSide_isLeft_FieldsideLeft()
{
	m_ballMock->setPosition(Point(-5.0,0.0));

	CPPUNIT_ASSERT_EQUAL(m_intelligentBall->getCurrentFieldSide(),FieldSideLeft);
}

void IntelligentBallTest::getShootingLineCoveragePercent_isZero_0()
{
	Compare compare(0.001);
	m_ballMock->setPosition(Point(0,0));
	m_ballMock->setObstacle(Circle(Point(0,0),0.03));
	Circle obstacleOne(Point(-0.5, 0.5), 0.075);
	Circle obstacleTwo(Point(0.5, 0.5), 0.075);
	vector<Circle> obstacleVector;
	obstacleVector.push_back(obstacleOne);
	obstacleVector.push_back(obstacleTwo);
	ObstacleFetcherMock obstacleFetcher;
	obstacleFetcher.setAllObstaclesButMe(obstacleVector);
	m_ballMock->setPosition(Point(0, 0));
	Point target(0, 1.0);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.0, m_intelligentBall->getShootingLineCoveragePercent(obstacleFetcher, target)));
}

void IntelligentBallTest::getShootingLineCoveragePercent_isHundred_100()
{
	Compare compare(0.001);
	m_ballMock->setPosition(Point(0,0));
	m_ballMock->setObstacle(Circle(Point(0,0),0.03));
	Circle obstacleOne(Point(0, 0.5), 0.075);
	Circle obstacleTwo(Point(0.5, 0.5), 0.075);
	vector<Circle> obstacleVector;
	obstacleVector.push_back(obstacleOne);
	obstacleVector.push_back(obstacleTwo);
	ObstacleFetcherMock obstacleFetcher;
	obstacleFetcher.setAllObstaclesButMe(obstacleVector);
	Point target(0, 1.0);
	double coverage = m_intelligentBall->getShootingLineCoveragePercent(obstacleFetcher, target);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(100.0, coverage));
}

void IntelligentBallTest::getShootingLineCoveragePercent_isFiftyRightofLine_50()
{
	Compare compare(0.001);
	m_ballMock->setPosition(Point(0,0));
	m_ballMock->setObstacle(Circle(Point(0,0),0.03));
	Circle obstacleTwo(Point(0.075/2.0, 0), 0.075);
	Circle obstacleOne(Point(0.5, 0.5), 0.075);
	vector<Circle> obstacleVector;
	obstacleVector.push_back(obstacleOne);
	obstacleVector.push_back(obstacleTwo);
	ObstacleFetcherMock obstacleFetcher;
	obstacleFetcher.setAllObstaclesButMe(obstacleVector);
	Point target(0, 1.0);
	double coverage = m_intelligentBall->getShootingLineCoveragePercent(obstacleFetcher, target);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(50.0, coverage));
}

void IntelligentBallTest::getShootingLineCoveragePercent_isFiftyLeftofLine_50()
{
	Compare compare(0.001);
	m_ballMock->setPosition(Point(0,0));
	m_ballMock->setObstacle(Circle(Point(0,0),0.03));
	Circle obstacleTwo(Point(-0.075/2.0, 0), 0.075);
	Circle obstacleOne(Point(0.5, 0.5), 0.075);
	vector<Circle> obstacleVector;
	obstacleVector.push_back(obstacleOne);
	obstacleVector.push_back(obstacleTwo);
	ObstacleFetcherMock obstacleFetcher;
	obstacleFetcher.setAllObstaclesButMe(obstacleVector);
	Point target(0, 1.0);
	double coverage = m_intelligentBall->getShootingLineCoveragePercent(obstacleFetcher, target);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(50.0, coverage));
}

void IntelligentBallTest::getShootingLineCoveragePercent_isHundredFiftyFromLeftFiftyFromRight_100()
{
	Compare compare(0.001);
	m_ballMock->setPosition(Point(0,0));
	m_ballMock->setObstacle(Circle(Point(0,0),0.03));
	Circle obstacleTwo(Point(-0.075/2.0, 0), 0.075);
	Circle obstacleOne(Point(0.075/2.0, 0.5), 0.075);
	Circle obstacleThree(Point(1, 0.5), 0.075);
	vector<Circle> obstacleVector;
	obstacleVector.push_back(obstacleOne);
	obstacleVector.push_back(obstacleTwo);
	obstacleVector.push_back(obstacleThree);
	ObstacleFetcherMock obstacleFetcher;
	obstacleFetcher.setAllObstaclesButMe(obstacleVector);
	Point target(0, 1.0);
	double coverage = m_intelligentBall->getShootingLineCoveragePercent(obstacleFetcher, target);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(100.0, coverage));
}

void IntelligentBallTest::getShootingLineCoveragePercent_isTwentyfiveFromLeftTwentyfiveFromRight_50()
{
	Compare compare(0.001);
	m_ballMock->setPosition(Point(0,0));
	m_ballMock->setObstacle(Circle(Point(0,0),0.03));
	Circle obstacleTwo(Point(-0.075/2.0-0.03/4.0, 0), 0.075);
	Circle obstacleOne(Point(0.075/2.0+0.03/4.0, 0.5), 0.075);
	Circle obstacleThree(Point(1, 0.5), 0.075);
	vector<Circle> obstacleVector;
	obstacleVector.push_back(obstacleOne);
	obstacleVector.push_back(obstacleTwo);
	obstacleVector.push_back(obstacleThree);
	ObstacleFetcherMock obstacleFetcher;
	obstacleFetcher.setAllObstaclesButMe(obstacleVector);
	Point target(0, 1.0);
	double coverage = m_intelligentBall->getShootingLineCoveragePercent(obstacleFetcher, target);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(50.0, coverage));
}
