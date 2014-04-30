#include "layer/control/robosoccerstatetest.h"
#include "layer/control/robosoccerstate.h"
#include "common/logging/loggermock.h"
#include "common/time/watchmock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/storagemock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/abstraction/ballmock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;

void RoboSoccerStateTest::setUp()
{
	m_referee = new RefereeMock();
	m_logger = new LoggerMock();
	m_enemyTeam = new EnemyTeamMock();
	m_ownTeam = new TeamMock();
	m_ball = new IntelligentBallMock();
	m_targetPositionFetcher = new TargetPositionFetcher();
	m_targetPositionFetcher->setFieldSide(FieldSideLeft);
	m_state = createInstance();
}

void RoboSoccerStateTest::tearDown()
{
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_ownTeam;
	m_ownTeam = 0;
	delete m_ball;
	m_ball = 0;
	delete m_state;
	m_state = 0;
	delete m_referee;
	m_referee = 0;
	delete m_logger;
	m_logger = 0;
}
