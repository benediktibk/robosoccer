#ifndef ROBOSOCCER_COMMON_STATES_STATEMACHINE_H
#define ROBOSOCCER_COMMON_STATES_STATEMACHINE_H

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
	class State;

	class StateMachine
	{
	public:
		StateMachine(State *initialState);
		~StateMachine();

		void update();
		const State& getCurrentState() const;
		std::string getNameOfCurrentState() const;
		bool allowLogMessages() const;

	private:
		void logStateChange(std::string const &stateName);

	private:
		State *m_currentState;
		Logging::Logger &m_logger;
	};
}
}
}

#endif
