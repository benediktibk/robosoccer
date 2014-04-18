#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTINGOBSTACLETEST_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTINGOBSTACLETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class RoutingObstacleTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RoutingObstacleTest);
		CPPUNIT_TEST(constructor_empty_isNotValid);
		CPPUNIT_TEST(constructor_validObstacle_isValid);
		CPPUNIT_TEST(constructor_wentRightBesideObstacle_wentRightBeside);
		CPPUNIT_TEST(constructor_wentLeftBesideObstacle_notWentRightBeside);
		CPPUNIT_TEST(constructor_validObstacle_getObstacleIsCorrect);
		CPPUNIT_TEST(operatorEqual_sameObstaclesButDifferentSide_false);
		CPPUNIT_TEST(operatorEqual_differentObstacles_false);
		CPPUNIT_TEST(operatorEqual_sameObstaclesAndSides_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_isNotValid();
		void constructor_validObstacle_isValid();
		void constructor_wentRightBesideObstacle_wentRightBeside();
		void constructor_wentLeftBesideObstacle_notWentRightBeside();
		void constructor_validObstacle_getObstacleIsCorrect();
		void operatorEqual_sameObstaclesButDifferentSide_false();
		void operatorEqual_differentObstacles_false();
		void operatorEqual_sameObstaclesAndSides_true();
	};
}
}
}

#endif


