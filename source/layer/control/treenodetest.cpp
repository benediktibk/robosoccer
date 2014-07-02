#include "layer/control/treenodetest.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/storagemock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/abstraction/ballmock.h"
#include "layer/control/treenodedecider.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;

void TreeNodeTest::setUp()
{
	m_referee = new RefereeMock();
	m_logger = new LoggerMock();
	m_enemyTeam = new EnemyTeamMock();
	m_ownTeam = new TeamMock();
	m_ball = new IntelligentBallMock();
	m_targetPositionFetcher = new TargetPositionFetcher();
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);
	m_node = createTestNode();
	m_lastFollowRobot = TreeNode::FollowBallRobotNone;
}

void TreeNodeTest::tearDown()
{
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_ownTeam;
	m_ownTeam = 0;
	delete m_ball;
	m_ball = 0;
	delete m_node;
	m_node = 0;
	delete m_referee;
	m_referee = 0;
	delete m_logger;
	m_logger = 0;
	delete m_targetPositionFetcher;
	m_targetPositionFetcher = 0;
}
