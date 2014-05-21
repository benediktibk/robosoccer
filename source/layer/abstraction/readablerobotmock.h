#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOTMOCK_H

#include "layer/abstraction/readablerobot.h"
#include "common/geometry/pose.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ReadableRobotMock :
			public ReadableRobot
	{
	public:
		virtual Common::Geometry::Pose getPose() const;
		virtual Common::Geometry::Circle getObstacle() const;

		void setPose(Common::Geometry::Pose const &pose);

	private:
		Common::Geometry::Pose m_pose;
	};
}
}
}

#endif


