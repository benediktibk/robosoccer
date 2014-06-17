#include "layer/control/treenodedeciderisonerobotinsidegoalzonetest.h"
#include "layer/control/treenodedeciderisonerobotinsidegoalzone.h"
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
