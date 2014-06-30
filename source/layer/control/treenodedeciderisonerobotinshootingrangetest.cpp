#include "layer/control/treenodedeciderisonerobotinshootingrangetest.h"
#include "layer/control/treenodedeciderisonerobotinshootingrange.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/control/treenodedeciderisonerobotbehindtheball.h"
#include "layer/control/treenoderesultshoot.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNode *TreeNodeDeciderIsOneRobotInShootingRangeTest::createTestNode()
{
	return new TreeNodeDeciderIsOneRobotInShootingRange(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher, m_lastFollowRobot);
}

void TreeNodeDeciderIsOneRobotInShootingRangeTest::decide_robotIsInShootingRange_shoot()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(-0.5,0.2), Angle()));
	m_ball->setPosition(Point (-0.4,0.2));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotInShootingRange*>(m_node)->getChild();
	TreeNodeDeciderIsOneRobotBehindTheBall *isBehindBall = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(result);
	TreeNodeResultShoot *shoot = dynamic_cast<TreeNodeResultShoot*>(result);

	CPPUNIT_ASSERT(isBehindBall == 0);
	CPPUNIT_ASSERT(shoot != 0);
	delete result;
}

void TreeNodeDeciderIsOneRobotInShootingRangeTest::decide_robotIsNotInShootingRange_isRobotBehindBall()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(1.5,0.2), Angle()));
	m_ball->setPosition(Point (-1.6,0.2));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotInShootingRange*>(m_node)->getChild();
	TreeNodeDeciderIsOneRobotBehindTheBall *isBehindBall = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(result);
	TreeNodeResultShoot *shoot = dynamic_cast<TreeNodeResultShoot*>(result);

	CPPUNIT_ASSERT(isBehindBall != 0);
	CPPUNIT_ASSERT(shoot == 0);
	delete result;
}

void TreeNodeDeciderIsOneRobotInShootingRangeTest::decide_robotIsInShootingRangeButOnWrongSide_isRobotBehindBall()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(1.5,0.2), Angle()));
	m_ball->setPosition(Point (1.6,0.2));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	//! @todo uncomment, when fixed
//	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotInShootingRange*>(m_node)->getChild();
//	TreeNodeDeciderIsOneRobotBehindTheBall *isBehindBall = dynamic_cast<TreeNodeDeciderIsOneRobotBehindTheBall*>(result);
//	TreeNodeResultShoot *shoot = dynamic_cast<TreeNodeResultShoot*>(result);

//	CPPUNIT_ASSERT(isBehindBall != 0);
//	CPPUNIT_ASSERT(shoot == 0);
//	delete result;
}
