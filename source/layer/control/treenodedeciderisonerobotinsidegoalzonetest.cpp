#include "layer/control/treenodedeciderisonerobotinsidegoalzonetest.h"
#include "layer/control/treenodedeciderisonerobotinsidegoalzone.h"
#include "layer/control/treenodedeciderisonerobotinshootingrange.h"
#include "layer/control/treenoderesultleavegoalzone.h"
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

TreeNode *TreeNodeDeciderIsOneRobotInsideGoalZoneTest::createTestNode()
{
	return new TreeNodeDeciderIsOneRobotInsideGoalZone(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void TreeNodeDeciderIsOneRobotInsideGoalZoneTest::decide_robotsAreInValidPosition_isInShootingRange()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(-0.5,0.2), Angle()));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotInsideGoalZone*>(m_node)->getChild();
	TreeNodeDeciderIsOneRobotInShootingRange *isInShootingRange = dynamic_cast<TreeNodeDeciderIsOneRobotInShootingRange*>(result);
	TreeNodeResultLeaveGoalZone *leaveGoalZone = dynamic_cast<TreeNodeResultLeaveGoalZone*>(result);

	CPPUNIT_ASSERT(isInShootingRange != 0);
	CPPUNIT_ASSERT(leaveGoalZone == 0);
	delete result;
}

void TreeNodeDeciderIsOneRobotInsideGoalZoneTest::decide_oneRobotInEnemyGoalZoneAndFieldSideLeft_leaveGoalZone()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(1.3,0.2), Angle()));
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);

	TreeNode *result = dynamic_cast<TreeNodeDeciderIsOneRobotInsideGoalZone*>(m_node)->getChild();
	TreeNodeDeciderIsOneRobotInShootingRange *isInShootingRange = dynamic_cast<TreeNodeDeciderIsOneRobotInShootingRange*>(result);
	TreeNodeResultLeaveGoalZone *leaveGoalZone = dynamic_cast<TreeNodeResultLeaveGoalZone*>(result);

	CPPUNIT_ASSERT(leaveGoalZone != 0);
	CPPUNIT_ASSERT(isInShootingRange == 0);
	delete result;
}
