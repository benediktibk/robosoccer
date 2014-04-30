#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class BallMock;
}
namespace Autonomous
{
	class IntelligentBallImpl;
	class IntelligentBallTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(IntelligentBallTest);
		CPPUNIT_TEST_SUITE_END();
	public:
		virtual void setUp();
		virtual void tearDown();
	private:
		Abstraction::BallMock *m_ballMock;
		Autonomous::IntelligentBallImpl *m_intelligentBall;
	};
}
}
}

#endif


