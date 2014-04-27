#ifndef ROBOSOCCER_LAYER_CONTROL_ROBOSOCCERSTATETEST_H
#define ROBOSOCCER_LAYER_CONTROL_ROBOSOCCERSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class LoggerMock;
}
}
namespace Layer
{
namespace Abstraction
{
	class RefereeMock;
}

namespace Control
{
	class RoboSoccerState;

	class RoboSoccerStateTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RoboSoccerState* createInstance() = 0;

	protected:
		RoboSoccerState *m_state;
		Abstraction::RefereeMock *m_referee;
		Common::Logging::LoggerMock *m_logger;
	};
}
}
}

#endif


