#include "layer/main/application.h"
#include "common/logging/logger.h"
#include "common/time/stopwatch.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;

Application::Application(Storage &storage, Logger &logger, const Watch &watch) :
	m_storage(storage),
	m_logger(logger),
	m_watch(watch)
{ }

void Application::run()
{
	bool stop = false;
	StopWatch stopWatch(m_watch);
	stopWatch.getTimeAndRestart();
	const double maximumLoopTime = 0.1;

	while (!stop)
	{
		// do some important stuff, like
		m_logger.logToConsoleAndGlobalLogFile("Die Wil Wheaton, die!");

		double loopTime = stopWatch.getTimeAndRestart();
		if (loopTime > maximumLoopTime)
			m_logger.logErrorToConsoleAndWriteToGlobalLogFile("loop time is too high");
	}
}

