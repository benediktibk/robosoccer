#include "layer/main/application.h"
#include "layer/main/fieldpositioncheckergoalkeeper.h"
#include "layer/main/fieldpositioncheckerfieldplayer.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/control/pause.h"
#include "common/logging/loggerimpl.h"
#include "common/time/stopwatch.h"
#include "common/time/watchimpl.h"
#include "common/states/statemachine.h"
#include <unistd.h>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::States;
using namespace std;

Application::Application(TeamColor ownTeamColor) :
	m_logger(new LoggerImpl()),
	m_watch(new WatchImpl()),
	m_storage(new StorageImpl(14, ownTeamColor, *m_logger, *m_watch)),
	m_fieldPositionCheckerGoalKeeper(new FieldPositionCheckerGoalkeeper),
	m_fieldPositionCheckerFieldPlayer(new FieldPositionCheckerFieldPlayer),
	m_obstacleFetcher(new ObstacleFetcher()),
	m_enemyTeam(new EnemyTeamImpl(*m_storage)),
	m_ownTeam(new TeamImpl(*m_storage, *m_watch, *m_logger, *m_fieldPositionCheckerGoalKeeper, *m_fieldPositionCheckerFieldPlayer, *m_obstacleFetcher)),
	m_ball(new IntelligentBallImpl(m_storage->getBall())),
	m_targetPositionFetcher(new TargetPositionFetcher()),
	m_stop(false)
{
	m_logger->logToConsoleAndGlobalLogFile("initialization finished");
}

Application::~Application()
{
	delete m_obstacleFetcher;
	m_obstacleFetcher = 0;
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_ownTeam;
	m_ownTeam = 0;
	delete m_fieldPositionCheckerGoalKeeper;
	m_fieldPositionCheckerGoalKeeper = 0;
	delete m_fieldPositionCheckerFieldPlayer;
	m_fieldPositionCheckerFieldPlayer = 0;
	delete m_ball;
	m_ball = 0;
	delete m_storage;
	m_storage = 0;
	delete m_watch;
	m_watch = 0;
	delete m_logger;
	m_logger = 0;
	delete m_targetPositionFetcher;
	m_targetPositionFetcher = 0;
}

void Application::run()
{
	StopWatch stopWatch(*m_watch);
	stopWatch.getTimeAndRestart();
	const double maximumLoopTime = 0.033;
	const double minimumLoopTime = 0.005;

	RefereeBase &referee = m_storage->getReferee();
	Pause *initialState = new Pause(*m_logger, referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
	StateMachine stateMachine(initialState);

	while (!m_stop)
	{
		FieldSide ownSide = referee.getOwnFieldSide();
		m_targetPositionFetcher->setFieldSide(ownSide);
		m_fieldPositionCheckerGoalKeeper->setTeamSide(ownSide);
		stateMachine.update();

		if (referee.playModeChangedSinceLastCall())
			referee.logInformation();

		for (unsigned int i = 0; i < 3; ++i)
		{
			Robot &robot = m_ownTeam->getRobotByNumber(i);
			robot.update();
		}

		double loopTime = stopWatch.getTimeAndRestart();

		if (loopTime < minimumLoopTime)
		{
			usleep((minimumLoopTime - loopTime)*1000000);
			loopTime += stopWatch.getTimeAndRestart();
		}

		if (loopTime > maximumLoopTime)
			m_logger->logErrorToConsoleAndWriteToGlobalLogFile("loop time is too high");
	}

	m_logger->logToConsoleAndGlobalLogFile("stopped");
}

void Application::stop()
{
	m_stop = true;
	m_logger->logToConsoleAndGlobalLogFile("stop requested");
}
