#include "layer/control/treenodedeciderisonerobotbehindtheballtest.h"
#include "layer/control/treenodedeciderisonerobotbehindtheball.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/control/treenoderesultdefendgoal.h"
#include "layer/control/treenoderesultshoot.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNode *TreeNodeDeciderIsOneRobotBehindTheBallTest::createTestNode()
{
	return new TreeNodeDeciderIsOneRobotBehindTheBall(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}
