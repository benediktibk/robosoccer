#include "layer/abstraction/robotturncontroltest.h"
#include "layer/abstraction/robotturncontrol.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include "common/geometry/pose.h"
#include "common/time/watchmock.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;

void RobotTurnControlTest::setUp()
{
	m_watch = new WatchMock();
	m_control = new RobotTurnControl(*m_watch);
}

void RobotTurnControlTest::tearDown()
{
	delete m_control;
	m_control = 0;
	delete m_watch;
	m_watch = 0;
}

void RobotTurnControlTest::evaluate_mustTurnRight_negtiveResult()
{
	Angle target(Angle::getEighthRotation());
	Angle current(Angle::getQuarterRotation());
	m_control->reset();

	double result = m_control->evaluate(current, target);

	CPPUNIT_ASSERT(result < 0);
}

void RobotTurnControlTest::evaluate_mustTurnLeft_positiveResult()
{
	Angle target(Angle::getHalfRotation());
	Angle current(Angle::getQuarterRotation());
	m_control->reset();

	double result = m_control->evaluate(current, target);

	CPPUNIT_ASSERT(result > 0);
}