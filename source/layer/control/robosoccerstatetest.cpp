#include "layer/control/robosoccerstatetest.h"
#include "layer/control/robosoccerstate.h"
#include "common/logging/loggermock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/storagemock.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;

void RoboSoccerStateTest::setUp()
{
	m_referee = new RefereeMock();
	m_logger = new LoggerMock();
	m_storage = new StorageMock();
	m_enemyTeam = new EnemyTeamImpl(*m_storage);
	m_ownTeam = new TeamImpl(*m_storage);
	m_ball = new IntelligentBall();
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
	delete m_storage;
	m_storage = 0;
	delete m_ball;
	m_ball = 0;
	delete m_state;
	m_state = 0;
	delete m_referee;
	m_referee = 0;
	delete m_logger;
	m_logger = 0;
}
