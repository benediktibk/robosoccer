#ifndef ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H
#define ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class OrientedPosition;
}
}
namespace Layer
{
namespace Main
{
class TargetPositionFetcher
{
public:
	TargetPositionFetcher();

	void setFieldSide(Layer::Abstraction::FieldSide fieldside);
	Common::Geometry::OrientedPosition getStartPosition() const;
	Common::Geometry::OrientedPosition getGoalPosition() const;

private:
	Layer::Abstraction::FieldSide m_fieldside;

};
}
}
}

#endif // ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHER_H


