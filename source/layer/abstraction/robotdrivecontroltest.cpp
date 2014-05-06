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
	m_control = new RobotDriveControl(*m_watch);
}

void RobotDriveControlTest::tearDown()
{
	delete m_control;
	m_control = 0;
	delete m_watch;
	m_watch = 0;
}

void RobotDriveControlTest::evaluate_atTarget_bothValuesCloseToZero()
{
	Pose current(Point(3, 4), Angle(0));
	Pose target(Point(3, 4), Angle(0));
	double translation;
	double rotation;

	m_control->evaluate(current, target, translation, rotation);

	CPPUNIT_ASSERT(translation < 0.1);
	CPPUNIT_ASSERT(rotation < 0.1);
}

void RobotDriveControlTest::evaluate_farAwayFromTarget_bigSpeed()
{
	Pose current(Point(3, 4), Angle(0));
	Pose target(Point(100, 100), Angle(0));
	double translation;
	double rotation;

	m_control->evaluate(current, target, translation, rotation);

	CPPUNIT_ASSERT(translation > 1);
}
