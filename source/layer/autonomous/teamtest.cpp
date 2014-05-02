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

	Robot const &playerFartherAway = m_teamImpl->getPlayerFartherAwayFromBall(ball);

	Pose firstPose = m_controllableRobotMockPlayer2->getPose();
	Pose secondPose = playerFartherAway.getCurrentPose();
	CPPUNIT_ASSERT(compare.isFuzzyEqual(firstPose, secondPose));
}
