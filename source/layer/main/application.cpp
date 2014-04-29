#include "layer/main/application.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/control/pause.h"
#include "layer/autonomous/enemyteam.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "common/logging/loggerimpl.h"
#include "common/time/stopwatch.h"
#include "common/time/watchimpl.h"
#include "common/states/statemachine.h"
#include "common/other/console.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Common::Other;

Application::Application(TeamColor ownTeamColor) :
	m_logger(new LoggerImpl()),
	m_storage(new StorageImpl(14, ownTeamColor, *m_logger)),
	m_watch(new WatchImpl()),
	m_enemyTeam(new EnemyTeam()),
	m_ownTeam(new Team(*m_storage)),
	m_ball(new IntelligentBall())
{ }

Application::~Application()
{
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_ownTeam;
	m_ownTeam = 0;
	delete m_ball;
	m_ball = 0;
	delete m_watch;
	m_watch = 0;
	delete m_storage;
	m_storage = 0;
	delete m_logger;
	m_logger = 0;
}

void Application::run()
{
	bool stop = false;
	StopWatch stopWatch(*m_watch);
	stopWatch.getTimeAndRestart();
	const double maximumLoopTime = 0.1;

	RefereeBase &referee = m_storage->getReferee();
	Pause *initialState = new Pause(*m_logger, referee);
	StateMachine stateMachine(initialState);

	while (!stop)
	{
		stateMachine.update();

		double loopTime = stopWatch.getTimeAndRestart();
		if (loopTime > maximumLoopTime)
			m_logger->logErrorToConsoleAndWriteToGlobalLogFile("loop time is too high");

		if (Console::getAsynchronousInput() == 'q')
			stop = true;
	}
}

