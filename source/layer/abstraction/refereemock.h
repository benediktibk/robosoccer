#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEMOCK_H

#include "layer/abstraction/refereebase.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeMock :
			public RefereeBase
	{
	public:
		RefereeMock();

		virtual FieldSide getOwnFieldSide() const;
		virtual bool getPrepareForKickOff() const;
		virtual bool getPrepareForPenalty() const;
		virtual bool hasKickOffOrPenalty() const;
		virtual bool getExecuteKickOff() const;
		virtual bool getExecutePenalty() const;
		virtual bool initFinished() const;
		virtual bool isGamePaused() const;
		virtual bool getContinuePlaying() const;
		virtual void setReady();
		virtual void logInformation();

		void setPrepareForKickOff(bool value);
		void setPrepareForPenalty(bool value);
		void setHasKickOffOrPenalty(bool value);
		void setExecuteKickOff(bool value);
		void setExecutePenalty(bool value);
		void setGamePaused(bool value);
		void setContinuePlaying(bool value);
		unsigned int getCallsToSetReady() const;

	private:
		bool m_prepareForKickOff;
		bool m_prepareForPenalty;
		bool m_hasKickOffOrPenalty;
		bool m_executeKickOff;
		bool m_executePenalty;
		bool m_gamePaused;
		bool m_continuePlaying;
		unsigned int m_callsToSetReady;
	};
}
}
}

#endif


