#ifndef ROBOSOCCER_COMMON_STATES_STATEMOCK_H
#define ROBOSOCCER_COMMON_STATES_STATEMOCK_H

#include "common/states/state.h"

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
	class StateMock :
			public State
	{
	public:
		StateMock(Logging::Logger &logger);
		StateMock(Logging::Logger &logger, bool callUpdateOnlyOnce);

		virtual State* nextState();
		virtual std::string getName();

		unsigned int getCallsToNextState() const;
		unsigned int getCallsToUpdate() const;
		void setNextState(State *state);

	protected:
		virtual void updateInternal();

	private:
		unsigned int m_callsToNextState;
		unsigned int m_callsToUpdate;
		State *m_nextState;
	};
}
}
}

#endif
