#include "layer/control/treenoderesultfollowballtest.h"
#include "layer/control/treenoderesultfollowball.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/control/treenoderesultgetbehindball.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNode *TreeNodeResultFollowBallTest::createTestNode()
{
	return new TreeNodeResultFollowBall(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher, m_lastFollowRobot);
}


void TreeNodeResultFollowBallTest::execute_true_bothRobotsGetGoToCalls()
{
	TreeNodeResultFollowBall *followBall = dynamic_cast<TreeNodeResultFollowBall*>(m_node);
	followBall->execute();

	CPPUNIT_ASSERT(!followBall->decide());
	CPPUNIT_ASSERT(m_ownTeam->getRobotMock().getCallsToGoTo() > 1);
}

void TreeNodeResultFollowBallTest::execute_noLastRobot_correctRobotIsChoosen()
{
	TreeNodeResultFollowBall *followBall = dynamic_cast<TreeNodeResultFollowBall*>(m_node);
	followBall->execute();
	CPPUNIT_ASSERT(followBall->getLastFollowBallRobot() != TreeNode::FollowBallRobotNone);

	followBall = new TreeNodeResultFollowBall(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher, TreeNode::FollowBallRobotOne);
	followBall->execute();
	CPPUNIT_ASSERT(followBall->getLastFollowBallRobot() != TreeNode::FollowBallRobotNone);
	CPPUNIT_ASSERT_EQUAL(TreeNode::FollowBallRobotOne, followBall->getLastFollowBallRobot());

	delete followBall;

	followBall = new TreeNodeResultFollowBall(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher, TreeNode::FollowBallRobotTwo);
	followBall->execute();
	CPPUNIT_ASSERT(followBall->getLastFollowBallRobot() != TreeNode::FollowBallRobotNone);
	CPPUNIT_ASSERT_EQUAL(TreeNode::FollowBallRobotTwo, followBall->getLastFollowBallRobot());
}
