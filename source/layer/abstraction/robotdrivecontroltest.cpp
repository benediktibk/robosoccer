#include "layer/abstraction/robotdrivecontroltest.h"
#include "layer/abstraction/robotdrivecontrol.h"
#include "common/time/watchmock.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;

void RobotDriveControlTest::setUp()
{
	m_watch = new WatchMock();
	m_control = new RobotDriveControl(*m_watch, 0.2, 0.2, 50, 40, 40);
}

void RobotDriveControlTest::tearDown()
{
	delete m_control;
	m_control = 0;
	delete m_watch;
	m_watch = 0;
}

void RobotDriveControlTest::evaluate_atTarget_bothValuesSmall()
{
	Pose current(Point(3, 4), Angle(0));
	Point target(3, 4);
	double translation;
	double rotation;

	m_control->evaluate(current, target, translation, rotation);

	CPPUNIT_ASSERT(translation < 10);
	CPPUNIT_ASSERT(rotation < 0.1);
}
