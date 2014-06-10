#ifndef ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERFIELDPLAYER_H
#define ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERFIELDPLAYER_H

#include "layer/abstraction/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class FieldPositionCheckerFieldPlayer :
			public FieldPositionChecker
	{
	public:
		FieldPositionCheckerFieldPlayer();

		virtual bool isPointInsideField(Common::Geometry::Point const &position) const;
	};
}
}
}

#endif