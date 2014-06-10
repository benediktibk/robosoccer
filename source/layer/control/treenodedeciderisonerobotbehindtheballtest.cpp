#include "layer/control/treenodedeciderisonerobotbehindtheballtest.h"
#include "layer/control/treenodedeciderisonerobotbehindtheball.h"
#include "common/logging/loggermock.h"
#include "common/geometry/pose.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/control/treenoderesultfollowball.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNode *TreeNodeDeciderIsOneRobotBehindTheBallTest::createTestNode()
{
	return new TreeNodeDeciderIsOneRobotBehindTheBall(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void TreeNodeDeciderIsOneRobotBehindTheBallTest::decide_bothRobotsBehindBall_followBall()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(-1.5,0.2), Angle()));
	m_ball->setPosition(Point (-1.4,0.2));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(m_node)->getChild();
	TreeNodeResultFollowBall *followBall = dynamic_cast<TreeNodeResultFollowBall*>(result);

	CPPUNIT_ASSERT(followBall != 0);
	delete result;
}

void TreeNodeDeciderIsOneRobotBehindTheBallTest::decide_oneRobotBehindBall_followBall()
{
	//! @todo implement
//	CPPUNIT_ASSERT(false);
}

void TreeNodeDeciderIsOneRobotBehindTheBallTest::decide_robotBehindBall_followBall()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(1.5,-0.2), Angle()));
	m_ball->setPosition(Point (1.65,-0.2));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(m_node)->getChild();
	TreeNodeResultFollowBall *followBall = dynamic_cast<TreeNodeResultFollowBall*>(result);
	TreeNodeResultGetBehindBall *getBehindBall = dynamic_cast<TreeNodeResultGetBehindBall*>(result);

	CPPUNIT_ASSERT(followBall != 0);
	CPPUNIT_ASSERT(getBehindBall == 0);
	delete result;
}

void TreeNodeDeciderIsOneRobotBehindTheBallTest::decide_robotBehindBallAndFieldSideIsRight_followBall()
{
	m_referee->setOwnFieldSide(FieldSideRight);
	m_targetPositionFetcher->setFieldSide(FieldSideRight);
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(-0.7,0.2), Angle()));
	m_ball->setPosition(Point (-0.9,0.2));

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(m_node)->getChild();
	TreeNodeResultFollowBall *followBall = dynamic_cast<TreeNodeResultFollowBall*>(result);
	TreeNodeResultGetBehindBall *getBehindBall = dynamic_cast<TreeNodeResultGetBehindBall*>(result);

	CPPUNIT_ASSERT(followBall != 0);
	CPPUNIT_ASSERT(getBehindBall == 0);
	delete result;
}

void TreeNodeDeciderIsOneRobotBehindTheBallTest::decide_robotIsNotBehindBallAndFieldSideIsRight_getBehindBall()
{
	m_referee->setOwnFieldSide(FieldSideRight);
	m_targetPositionFetcher->setFieldSide(FieldSideRight);
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(-0.9,0.2), Angle()));
	m_ball->setPosition(Point (-0.7,0.2));

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(m_node)->getChild();
	TreeNodeResultFollowBall *followBall = dynamic_cast<TreeNodeResultFollowBall*>(result);
	TreeNodeResultGetBehindBall *getBehindBall = dynamic_cast<TreeNodeResultGetBehindBall*>(result);

	CPPUNIT_ASSERT(followBall == 0);
	CPPUNIT_ASSERT(getBehindBall != 0);
	delete result;
}
