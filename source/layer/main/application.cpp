#include "layer/main/application.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/control/pause.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/logging/loggerimpl.h"
#include "common/time/stopwatch.h"
#include "common/time/watchimpl.h"
#include "common/states/statemachine.h"
#include "common/other/console.h"
#include "layer/autonomous/robot.h"
#include "layer/main/fieldpositioncheckergoalkeeper.h"
#include "layer/main/fieldpositioncheckerfieldplayer.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Common::Other;
using namespace std;

Application::Application(TeamColor ownTeamColor) :
	m_logger(new LoggerImpl()),
	m_watch(new WatchImpl()),
	m_storage(new StorageImpl(14, ownTeamColor, *m_logger, *m_watch)),
	m_fieldPositionCheckerGoalKeeper(new FieldPositionCheckerGoalkeeper),
	m_fieldPositionCheckerFieldPlayer(new FieldPositionCheckerFieldPlayer),
	m_enemyTeam(new EnemyTeamImpl(*m_storage)),
	m_ownTeam(new TeamImpl(*m_storage, *m_watch, *m_logger, *m_fieldPositionCheckerGoalKeeper, *m_fieldPositionCheckerFieldPlayer)),
	m_ball(new IntelligentBallImpl(m_storage->getBall())),
	m_targetPositionFetcher(new TargetPositionFetcher())
{ }

Application::~Application()
{
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
	bool stop = false;
	StopWatch stopWatch(*m_watch);
	stopWatch.getTimeAndRestart();
	const double maximumLoopTime = 0.1;
	const double minimumLoopTime = 0.005;

	RefereeBase &referee = m_storage->getReferee();
	Pause *initialState = new Pause(*m_logger, referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
	StateMachine stateMachine(initialState);

	while (!stop)
	{
		for (unsigned int i = 0; i < 3; ++i)
		{
			Robot &robot = m_ownTeam->getRobotByNumber(i);
			robot.measure();
		}

		FieldSide ownSide = referee.getOwnFieldSide();
		m_targetPositionFetcher->setFieldSide(ownSide);
		m_fieldPositionCheckerGoalKeeper->setTeamSide(ownSide);
		string previousState = stateMachine.getNameOfCurrentState();
		stateMachine.update();
		string currentState = stateMachine.getNameOfCurrentState();

		if (previousState != currentState)
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

		if (Console::getAsynchronousInput() == 'q')
			stop = true;
	}
}
