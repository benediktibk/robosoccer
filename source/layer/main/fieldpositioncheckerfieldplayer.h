#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERFIELDPLAYER_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERFIELDPLAYER_H

#include "layer/main/fieldpositionchecker.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Main
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