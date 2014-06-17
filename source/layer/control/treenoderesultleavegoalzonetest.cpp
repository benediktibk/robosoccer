#include "layer/control/treenoderesultleavegoalzonetest.h"
#include "layer/control/treenoderesultleavegoalzone.h"
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

TreeNode *TreeNodeResultLeaveGoalZoneTest::createTestNode()
{
	return new TreeNodeResultLeaveGoalZone(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}


void TreeNodeResultLeaveGoalZoneTest::execute_true_robotsGetGoToCalls()
{
	m_ownTeam->getRobotMock().setCurrentPose(Pose(Point(-1.3,0.2), Angle()));

	TreeNodeResultLeaveGoalZone *leaveGoalZone = dynamic_cast<TreeNodeResultLeaveGoalZone*>(m_node);
	leaveGoalZone->execute();

	CPPUNIT_ASSERT(!leaveGoalZone->decide());
	CPPUNIT_ASSERT(m_ownTeam->getRobotMock().getCallsToGoTo() > 0);
}
