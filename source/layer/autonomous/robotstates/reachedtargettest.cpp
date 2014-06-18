#include "layer/autonomous/robotstates/reachedtargettest.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotState *ReachedTargetTest::createInstance()
{
	return new ReachedTarget(*m_controllableRobot, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void ReachedTargetTest::reachedTarget_empty_true()
{
	CPPUNIT_ASSERT(m_robotState->reachedTarget());
}

void ReachedTargetTest::nextState_empty_0()
{
	CPPUNIT_ASSERT(m_robotState->nextState(false) == 0);
}

void ReachedTargetTest::update_empty_callToStop()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToStop());
}

void ReachedTargetTest::isEquivalentToDriveTo_differentPosition_false()
{
	m_controllableRobot->setPose(Pose(Point(4, 5), Angle()));
	vector<Pose> pose;
	pose.push_back(Pose(Point(3, 7),Angle()));

	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(pose));
}

void ReachedTargetTest::isEquivalentToDriveTo_samePosition_true()
{
	m_controllableRobot->setPose(Pose(Point(4, 5), Angle()));
	vector<Pose> pose;
	pose.push_back(Pose(Point(4, 5),Angle()));

	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(pose));
}
