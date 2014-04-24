#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H

#include "layer/abstraction/refereebase.h"
#include "layer/abstraction/teamcolor.h"
#include <string>

class Referee;

namespace KogniMobil
{
	class RTDBConn;
}

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class RefereeImpl :
			public RefereeBase
	{
	public:
		RefereeImpl(KogniMobil::RTDBConn &dataBase, TeamColor ownColor, Common::Logging::Logger &logger);
		virtual ~RefereeImpl();

		virtual FieldSide getOwnFieldSide() const;
		virtual bool getPrepareForKickOff() const;
		virtual bool getPrepareForPenalty() const;
		virtual bool hasKickOffOrPenalty() const;
		virtual bool getExecuteKickOff() const;
		virtual bool getExecutePenalty() const;
		virtual bool initFinished() const;
		virtual bool isGamePaused() const;
		virtual void logInformation();

	private:
		void logBool(const char *message, bool value);
		void logBool(std::string const &message, bool value);
		void logFieldSide(const char *message, FieldSide fieldSide);

	private:
		Common::Logging::Logger &m_logger;
		Referee *m_referee;
		TeamColor m_ownColor;
	};
}
}
}

#endif


