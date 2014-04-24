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
		virtual FieldSide getOwnFieldSide() const;
		virtual bool getPrepareForKickOff() const;
		virtual bool getPrepareForPenalty() const;
		virtual bool hasKickOffOrPenalty() const;
		virtual bool getExecuteKickOff() const;
		virtual bool getExecutePenalty() const;
		virtual bool initFinished() const;
		virtual bool isGamePaused() const;
		virtual void logInformation();
	};
}
}
}

#endif


