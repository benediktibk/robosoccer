#include "layer/control/treenoderesultdefendgoaltest.h"
#include "layer/control/treenoderesultdefendgoal.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/control/treenoderesultdefendgoal.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNode *TreeNodeResultDefendGoalTest::createTestNode()
{
	return new TreeNodeResultDefendGoal(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);;
}

void TreeNodeResultDefendGoalTest::execute_bothRobotsShouldMove_moveMethodsGetCalled()
{
	const RobotMock &robot1 = m_ownTeam->getRobotMock();

	((TreeNodeResult*)m_node)->execute();

	CPPUNIT_ASSERT(robot1.getCallsToGoToCombined() > 0);
}
