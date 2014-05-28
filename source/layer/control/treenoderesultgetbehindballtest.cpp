#include "layer/control/treenoderesultgetbehindballtest.h"
#include "layer/control/treenoderesultgetbehindball.h"
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

TreeNode *TreeNodeResultGetBehindBallTest::createTestNode()
{
	return new TreeNodeResultGetBehindBall(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);;
}