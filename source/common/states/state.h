#ifndef ROBOSOCCER_COMMON_STATES_STATE_H
#define ROBOSOCCER_COMMON_STATES_STATE_H

#include <string>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
namespace States
{
	class State
	{
	public:
		State(Logging::Logger &logger, bool callUpdateOnlyOnce);
		virtual ~State();

		virtual State* nextState() = 0;
		void update();
		virtual std::string getName() = 0;
		virtual bool allowLogMessages();
		bool updateAlreadyCalled() const;

	protected:
		virtual void updateInternal() = 0;

	protected:
		Logging::Logger &m_logger;

	private:
		bool m_callUpdateOnlyOnce;
		bool m_updateAlreadyCalled;
	};
}
}
}

#endif
