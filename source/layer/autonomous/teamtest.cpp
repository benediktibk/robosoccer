#include "layer/autonomous/teamtest.h"
#include "layer/autonomous/teamimpl.h"
#include "common/logging/loggermock.h"
#include "common/time/watchmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "layer/abstraction/storagemock.h"
#include <vector>
#include "common/geometry/pose.h"
#include "layer/autonomous/intelligentballmock.h"
#include "common/geometry/compare.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

void TeamTest::setUp()
{
	m_loggerMock = new LoggerMock;
	m_watchMock = new WatchMock;
	m_controllableRobotMockGoalie = new ControllableRobotMock;
	m_controllableRobotMockPlayer1 = new ControllableRobotMock;
	m_controllableRobotMockPlayer2 = new ControllableRobotMock;
	m_storageMock = new StorageMock;
	m_controllableRobotMockGoalie = &(m_storageMock->getOwnRobotMock(0));
	m_controllableRobotMockPlayer1 = &(m_storageMock->getOwnRobotMock(1));
	m_controllableRobotMockPlayer2 = &(m_storageMock->getOwnRobotMock(2));
	m_teamImpl = new TeamImpl(*m_storageMock, *m_watchMock, *m_loggerMock);
}

void TeamTest::tearDown()
{
	delete m_teamImpl;
	m_teamImpl = 0;
	delete m_storageMock;
	m_storageMock = 0;
	m_controllableRobotMockGoalie = 0;
	m_controllableRobotMockPlayer1 = 0;
	m_controllableRobotMockPlayer2 = 0;
	delete m_watchMock;
	m_watchMock = 0;
	delete m_loggerMock;
	m_loggerMock = 0;
}

void TeamTest::getPlayerCloserToBall_playerOneCloser_correct()
{
	Compare compare(0.001);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5,0));
	m_controllableRobotMockPlayer1->setPose(Pose(Point(0,0),Angle()));
	m_controllableRobotMockPlayer2->setPose(Pose(Point(1,1),Angle()));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(m_controllableRobotMockPlayer1->getPose(),m_teamImpl->getPlayerCloserToBall(ball).getCurrentPose()));
}

void TeamTest::getPlayerFartherAwayFromBall_playerOneCloser_correct()
{
	Compare compare(0.001);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5,0));
	m_controllableRobotMockPlayer1->setPose(Pose(Point(0,0),Angle()));
	m_controllableRobotMockPlayer2->setPose(Pose(Point(1,1),Angle()));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(m_controllableRobotMockPlayer2->getPose(),m_teamImpl->getPlayerFartherAwayFromBall(ball).getCurrentPose()));
}

void TeamTest::getFirstFieldPlayer_empty_notTheGoalie()
{
	Robot &goalie = m_teamImpl->getGoalie();
	Robot &fieldPlayer = m_teamImpl->getFirstFieldPlayer();

	CPPUNIT_ASSERT(&goalie != &fieldPlayer);
}

void TeamTest::getSecondFieldPlayer_empty_notTheGoalie()
{
	Robot &goalie = m_teamImpl->getGoalie();
	Robot &fieldPlayer = m_teamImpl->getSecondFieldPlayer();

	CPPUNIT_ASSERT(&goalie != &fieldPlayer);
}

void TeamTest::getSecondFieldPlayer_empty_notTheFirstFieldPlayer()
{
	Robot &firstFieldPlayer = m_teamImpl->getFirstFieldPlayer();
	Robot &secondFieldPlayer = m_teamImpl->getSecondFieldPlayer();

	CPPUNIT_ASSERT(&firstFieldPlayer != &secondFieldPlayer);
}

void TeamTest::getObstacles_empty_obstacleSizeIs3()
{
	CPPUNIT_ASSERT_EQUAL((size_t)3, m_teamImpl->getObstacles().size());
}

void TeamTest::getObstacles_firstAtOrigin_obstacleCorrect()
{
	Compare compare(0.001);
	m_controllableRobotMockPlayer1->setPose(Pose(Point(0,0),Angle()));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(m_teamImpl->getObstacles().front(),Circle(Point(0,0),0.095)));
}
