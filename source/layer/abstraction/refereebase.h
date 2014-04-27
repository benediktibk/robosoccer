#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEBASE_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEBASE_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeBase
	{
	public:
		virtual ~RefereeBase() {}

		virtual FieldSide getOwnFieldSide() const = 0;
		virtual bool getPrepareForKickOff() const = 0;
		virtual bool getPrepareForPenalty() const = 0;
		virtual bool hasKickOffOrPenalty() const = 0;
		virtual bool getExecuteKickOff() const = 0;
		virtual bool getExecutePenalty() const = 0;
		virtual bool initFinished() const = 0;
		virtual bool isGamePaused() const = 0;
		virtual bool getContinuePlaying() const = 0;
		virtual void setReady() = 0;
		virtual void logInformation() = 0;
	};
}
}
}

#endif


