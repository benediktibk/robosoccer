#ifndef ROBOSOCCER_LAYER_MAIN_APPLICATION_H
#define ROBOSOCCER_LAYER_MAIN_APPLICATION_H

#include "layer/abstraction/teamcolor.h"

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
		Application(Abstraction::TeamColor ownTeamColor);
		~Application();

		void run();

	private:
		Common::Logging::Logger *m_logger;
		Abstraction::Storage *m_storage;
		Common::Time::Watch *m_watch;
	};
}
}
}

#endif


