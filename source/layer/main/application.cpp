#include "layer/main/application.h"
#include "common/logging/logger.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;

Application::Application(Storage &storage, Common::Logging::Logger &logger) :
	m_storage(storage),
	m_logger(logger)
{ }

void Application::run()
{
	m_logger.logToConsoleAndGlobalLogFile("Die Wil Wheaton, die!");
}

