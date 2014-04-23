#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H

#include "layer/abstraction/refereebase.h"
#include "layer/abstraction/teamcolor.h"

class Referee;

namespace KogniMobil
{
	class RTDBConn;
}

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeImpl :
			public RefereeBase
	{
	public:
		RefereeImpl(KogniMobil::RTDBConn &dataBase, TeamColor ownColor);
		virtual ~RefereeImpl();

		virtual FieldSide getOwnFieldSide() const;

	private:
		Referee *m_referee;
		TeamColor m_ownColor;
	};
}
}
}

#endif


