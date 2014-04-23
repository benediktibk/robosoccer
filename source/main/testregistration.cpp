#include "common/geometry/angletest.h"
#include "common/geometry/circletest.h"
#include "common/geometry/linetest.h"
#include "common/geometry/pathintersectpointstest.h"
#include "common/geometry/pathtest.h"
#include "common/geometry/pointtest.h"
#include "common/geometry/pointdistancecomparetest.h"
#include "common/geometry/rectangletest.h"
#include "common/geometry/orientedpositiontest.h"
#include "common/geometry/rectangleroundedcornerstest.h"
#include "common/logging/loggertest.h"
#include "common/other/comparetest.h"
#include "common/other/pidcontrollertest.h"
#include "common/other/quadraticequationtest.h"
#include "common/other/randomdecisiontest.h"
#include "common/other/signumtest.h"
#include "common/routing/routelengthcomparetest.h"
#include "common/routing/routertest.h"
#include "common/routing/routetest.h"
#include "common/routing/routingobstacletest.h"
#include "common/routing/routingresulttest.h"
#include "common/time/stopwatchtest.h"
#include "common/time/watchtest.h"
#include "common/states/statetest.h"
#include "common/states/statemachinetest.h"
#include "layer/main/applicationtest.h"
#include "layer/main/fieldpositioncheckerfieldplayertest.h"
#include "layer/main/fieldpositioncheckergoalkeepertest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::AngleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::CircleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::LineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::PathIntersectPointsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::PathTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::PointDistanceCompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::RectangleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::OrientedPositionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Geometry::RectangleRoundedCornersTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Logging::LoggerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Other::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Other::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Other::PIDControllerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Other::QuadraticEquationTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Other::RandomDecisionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Other::SignumTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Routing::RouteLengthCompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Routing::RouterTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Routing::RouteTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Routing::RoutingObstacleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Routing::RoutingResultTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Time::StopWatchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::Time::WatchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::States::StateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Common::States::StateMachineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Layer::Main::ApplicationTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Layer::Main::FieldPositionCheckerFieldPlayerTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboSoccer::Layer::Main::FieldPositionCheckerGoalkeeperTest);
