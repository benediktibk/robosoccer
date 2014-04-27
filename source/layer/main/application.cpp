#include "layer/main/application.h"
#include "layer/abstraction/storage.h"
#include "layer/control/pause.h"
#include "common/logging/logger.h"
#include "common/time/stopwatch.h"
#include "common/states/statemachine.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::States;

Application::Application(Storage &storage, Logger &logger, const Watch &watch) :
	m_storage(storage),
	m_logger(logger),
	m_watch(watch),
	m_stateMachine(0)
{
	RefereeBase &referee = m_storage.getReferee();
	Pause *initialState = new Pause(m_logger, referee);
	m_stateMachine = new StateMachine(initialState);
}

Application::~Application()
{
	delete m_stateMachine;
	m_stateMachine = 0;
}

void Application::run()
{
	bool stop = false;
	StopWatch stopWatch(m_watch);
	stopWatch.getTimeAndRestart();
	const double maximumLoopTime = 0.1;

	while (!stop)
	{
		m_stateMachine->update();

		double loopTime = stopWatch.getTimeAndRestart();
		if (loopTime > maximumLoopTime)
			m_logger.logErrorToConsoleAndWriteToGlobalLogFile("loop time is too high");
	}
}

