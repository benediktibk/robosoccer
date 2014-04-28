#ifndef ROBOSOCCER_LAYER_MAIN_APPLICATION_H
#define ROBOSOCCER_LAYER_MAIN_APPLICATION_H

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
namespace Time
{
	class Watch;
}
namespace States
{
	class StateMachine;
}
}
namespace Layer
{
namespace Abstraction
{
	class Storage;
}
namespace Main
{
	class Application
	{
	public:
		Application(Abstraction::Storage &storage, Common::Logging::Logger &logger, Common::Time::Watch const &watch);
		~Application();

		void run();

	private:
		Abstraction::Storage &m_storage;
		Common::Logging::Logger &m_logger;
		Common::Time::Watch const &m_watch;
		Common::States::StateMachine *m_stateMachine;
	};
}
}
}

#endif


