#include "common/routing/routertest.h"
#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositioncheckermock.h"
#include "common/routing/route.h"
#include "common/routing/routingobstacle.h"
#include "common/geometry/compare.h"
#include "common/geometry/path.h"
#include "common/time/watchimpl.h"
#include "common/geometry/angle.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/line.h"
#include "common/other/signum.h"
#include "common/geometry/pathintersectpoints.h"
#include "common/time/stopwatch.h"
#include <assert.h>

using namespace std;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;

const vector<Circle> RouterTest::m_noObstacles;

void RouterTest::calculateRoute_emptyField_validRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 2), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_emptyField_routeHasTwoPoints()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 2), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, m_noObstacles);

	CPPUNIT_ASSERT_EQUAL((size_t)2, route.getPointCount());
}

void RouterTest::calculateRoute_emptyField_routeHasSameWidthAsRobot()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 2), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, m_noObstacles);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, route.getWidth(), 0.00001);
}

void RouterTest::calculateRoute_softObstacleAtEndOfRoute_invalidRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 10), 0.1));
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 10), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_oneObstacleBetween_validRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 10), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneObstacleBetween_routeIsNotTooLong()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 10), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 9.5);
}

void RouterTest::calculateRoute_oneObstacleBetween_routeIsNotIntersectingWithObstacles()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	OrientedPosition start(Point(1, 1), Angle::getQuarterRotation());
	OrientedPosition end(Point(1, 10), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_validRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_validRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5.5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, obstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5.5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5.5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, -0.7), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 5.5);
}

void RouterTest::calculateRoute_oneBigObstacleOnLeftSideOfDirectPath_reasonableRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 0.7), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 5.5);
}

void RouterTest::calculateRoute_obstacleOnWayToPointBesideObstacle_reasonableRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 0), 2));
	obstacles.push_back(Circle(Point(1, -1), 1));
	obstacles.push_back(Circle(Point(1, 1), 1));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(5, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_obstacleOnWayToTargetFromPointBesideObstacle_reasonableRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 0), 2));
	obstacles.push_back(Circle(Point(5, -1), 1));
	obstacles.push_back(Circle(Point(5, 1), 1));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 11);
}

void RouterTest::calculateRoute_obstacleOnWayToAndFromPointBesideObstacle_reasonableRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 0), 2));
	obstacles.push_back(Circle(Point(1, -1), 1));
	obstacles.push_back(Circle(Point(1, 1), 1));
	obstacles.push_back(Circle(Point(5, -1), 1));
	obstacles.push_back(Circle(Point(5, 1), 1));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 11.5);
}

void RouterTest::calculateRoute_goingBetweenTwoObstacles_directRoute()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, -0.8), 1));
	obstacles.push_back(Circle(Point(1, 0.8), 1));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(2, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, routeLength, 0.01);
}

void RouterTest::calculateRoute_severalObjectsAndOneOnTheWay_calculationIsNotTooSlow()
{
	FieldPositionCheckerMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, 0), 0.1));
	obstacles.push_back(Circle(Point(0.5, 0), 0.1));
	obstacles.push_back(Circle(Point(2, 0), 0.1));
	obstacles.push_back(Circle(Point(3.5, 0), 0.1));
	obstacles.push_back(Circle(Point(4, 0), 0.1));
	obstacles.push_back(Circle(Point(0, 7), 0.1));
	obstacles.push_back(Circle(Point(0.5, 7), 0.1));
	obstacles.push_back(Circle(Point(2, 7), 0.1));
	obstacles.push_back(Circle(Point(3.5, 7), 0.1));
	obstacles.push_back(Circle(Point(4, 7), 0.1));
	obstacles.push_back(Circle(Point(2, 2), 0.1));
	obstacles.push_back(Circle(Point(0, 5), 0.1));
	obstacles.push_back(Circle(Point(0.5, 5), 0.1));
	obstacles.push_back(Circle(Point(2, 5), 0.1));
	obstacles.push_back(Circle(Point(3.5, 5), 0.1));
	obstacles.push_back(Circle(Point(4, 5), 0.1));
	OrientedPosition start(Point(1, 2), 0);
	OrientedPosition end(Point(3, 2), 0);

	WatchImpl watch;
	StopWatch stopWatch(watch);
	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);
	double time = stopWatch.getTimeAndRestart();

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	CPPUNIT_ASSERT(time < 0.2);
}

void RouterTest::calculateRoute_shortWayOutsideField_noPointOfRouteIsOutside()
{
	FieldPositionCheckerMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 1), 2));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	CPPUNIT_ASSERT(routeIsInsideField(route, field));
}

void RouterTest::calculateRoute_onlyPossiblePointBesideIsBlockedByAnotherObstacle_reasonableRoute()
{
	FieldPositionCheckerMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 1), 2));
	obstacles.push_back(Circle(Point(5, 2.5), 1));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 12.5);
}

void RouterTest::calculateRoute_softObstacleAtOwnPosition_validRoute()
{
	FieldPositionCheckerMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, 0), 0.1));
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field, Angle::getHalfRotation(), 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_completeTurnAtStartNecessaryAndMaximumRotation_reasonableRoute()
{
	OrientedPosition start(Point(0, 0), Angle::getHalfRotation());
	OrientedPosition end(Point(10, 0), 0);
	Angle maximumRotation = Angle::getQuarterRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, m_noObstacles, m_noObstacles);

	Other::Compare compare(0.001);
	CPPUNIT_ASSERT(route.isValid());
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(compare.isStrictFuzzyGreater(routeLength, 10));
	Angle maximumBend = route.getMaximumBend(Angle::getHalfRotation(), Angle(0));
	CPPUNIT_ASSERT(compare.isFuzzySmaller(maximumBend.getValueBetweenZeroAndTwoPi(), maximumRotation.getValueBetweenZeroAndTwoPi()));
}

void RouterTest::calculateRoute_completeTurnAtEndNecessaryAndMaximumRotation_reasonableRoute()
{
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), Angle::getHalfRotation());
	Angle maximumRotation = Angle::getQuarterRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, m_noObstacles, m_noObstacles);

	Other::Compare compare(0.001);
	CPPUNIT_ASSERT(route.isValid());
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(compare.isStrictFuzzyGreater(routeLength, 10));
	Angle maximumBend = route.getMaximumBend(Angle(0), Angle::getHalfRotation());
	CPPUNIT_ASSERT(compare.isFuzzySmaller(maximumBend.getValueBetweenZeroAndTwoPi(), maximumRotation.getValueBetweenZeroAndTwoPi()));
}

void RouterTest::calculateRoute_sharpBendBetweenNecessary_reasonableRoute()
{
	OrientedPosition start(Point(0, 0.5), Angle(1.16321775021193));
	OrientedPosition end(Point(4, 0.5), Angle(-1.16321775021193));
	Angle maximumRotation = Angle::getEighthRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	field.setNegativeCoordinatesOutside(true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 0), 1));
	obstacles.push_back(Circle(Point(2, 1), 1));
	obstacles.push_back(Circle(Point(2, 2), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, obstacles, m_noObstacles);

	Other::Compare compare(0.001);
	CPPUNIT_ASSERT(route.isValid());
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(compare.isStrictFuzzyGreater(routeLength, 4));
	Angle maximumBend = route.getMaximumBend(start.getOrientation(), end.getOrientation());
	CPPUNIT_ASSERT(compare.isFuzzySmaller(maximumBend.getValueBetweenZeroAndTwoPi(), maximumRotation.getValueBetweenZeroAndTwoPi()));
}

void RouterTest::calculateRoute_endRotationNotPossibleBecauseOfObstacles_invalidRoute()
{
	OrientedPosition start(Point(0, 0), 0);
	OrientedPosition end(Point(10, 0), Angle::getHalfRotation());
	Angle maximumRotation = Angle::getQuarterRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, -1), 1));
	obstacles.push_back(Circle(Point(10, 1), 1));
	obstacles.push_back(Circle(Point(11, 0), 1));

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.5, false, obstacles, m_noObstacles);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_twoSmallObstaclesVeryClose_validRoute()
{
	OrientedPosition start(Point(0.18, 0.435), Angle(-1.60978710380646));
	OrientedPosition end(Point(0.2625, -0.4625), Angle(-1.60978710380646));
	Angle maximumRotation = Angle::getHalfRotation();
	RouterImpl router(0.38);
	FieldPositionCheckerMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, 0), 0.1));
	obstacles.push_back(Circle(Point(0.4, 0), 0.1));

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, obstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_targetOutsideOfTheField_invalidRoute()
{
	OrientedPosition start(Point(1, 1), Angle::getThreeQuarterRotation());
	OrientedPosition end(Point(1, -1), Angle::getThreeQuarterRotation());
	Angle maximumRotation = Angle::getHalfRotation();
	RouterImpl router(0.38);
	FieldPositionCheckerMock field;
	field.setNegativeCoordinatesOutside(true);

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, m_noObstacles, m_noObstacles);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_completeTurnAtEndAndIgnoreFinalOrientation_directConnection()
{
	OrientedPosition start(Point(0, 0), Angle(0));
	OrientedPosition end(Point(10, 0), Angle::getHalfRotation());
	Angle maximumRotation = Angle::getQuarterRotation();
	RouterImpl router(0.38);
	FieldPositionCheckerMock field;

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, true, m_noObstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
	double routeLength = route.getLength();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(10, routeLength, 0.001);
}

void RouterTest::calculateRoute_hardObstacleInsideStartPosition_directConnection()
{
	OrientedPosition start(Point(0, 0), Angle(0));
	OrientedPosition end(Point(10, 0), Angle::getHalfRotation());
	Angle maximumRotation = Angle::getHalfRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0.1, 0), 2));

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, obstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
	double routeLength = route.getLength();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(10, routeLength, 0.001);
}

void RouterTest::calculateRoute_hardObstacleIntersectingWithStartPosition_reasonableRoute()
{
	OrientedPosition start(Point(0, 0), Angle(0));
	OrientedPosition end(Point(10, 0), Angle::getHalfRotation());
	Angle maximumRotation = Angle::getHalfRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 0), 2));

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, obstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength > 10.1);
	CPPUNIT_ASSERT(routeLength < 11);
}

void RouterTest::calculateRoute_targetInsideSoftObstacle_invalidRoute()
{
	OrientedPosition start(Point(0, 0), Angle(0));
	OrientedPosition end(Point(10, 0), Angle(0));
	Angle maximumRotation = Angle::getHalfRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, m_noObstacles, obstacles);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_startIsOutsideTheField_validRoute()
{
	OrientedPosition start(Point(0, -1), Angle::getThreeQuarterRotation());
	OrientedPosition end(Point(0, 5), Angle::getQuarterRotation());
	Angle maximumRotation = Angle::getQuarterRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	field.setNegativeCoordinatesOutside(true);

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, m_noObstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_startIsOutsideTheFieldAndAnObstacleOnTheWay_validRoute()
{
	OrientedPosition start(Point(0, -10), Angle::getQuarterRotation());
	OrientedPosition end(Point(0, 10), Angle::getQuarterRotation());
	Angle maximumRotation = Angle::getQuarterRotation();
	RouterImpl router(0.5);
	FieldPositionCheckerMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, -5), 1));
	field.setNegativeCoordinatesOutside(true);

	Route route = router.calculateRoute(start, end, field, maximumRotation, 0.1, false, obstacles, m_noObstacles);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(0,2), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(2,0), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(1,2), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(2,1), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2()
{
	RouterImpl router(0.5);
	Path path(Point(1, 1), Point(1, 10), 0.5);
	Circle obstacle(Point(1, 5), 0.1);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pointsBeside.size());
}

void RouterTest::getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,0.5), 0.5);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 0.35);
}

void RouterTest::getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,0.5), 0.5);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 0.35);
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_resultSizeIs2()
{
	RouterImpl router(0.5);
	Path path(Point(0, 0), Point(5, 0), 0.5);
	Circle obstacle(Point(2, -0.7), 2);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pointsBeside.size());
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsDoNotIntersectWithTheObstacle()
{
	RouterImpl router(0.5);
	Path path(Point(0, 0), Point(5, 0), 0.5);
	Circle obstacle(Point(2, -0.7), 2);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	Circle one(pointsBeside.front(), 0.707);
	Circle two(pointsBeside.back(), 0.707);
	CPPUNIT_ASSERT(!one.overlapsWith(obstacle));
	CPPUNIT_ASSERT(!two.overlapsWith(obstacle));
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsHaveReasonableCoordinates()
{
	RouterImpl router(0.5);
	Path path(Point(0, 0), Point(5, 0), 0.5);
	Circle obstacle(Point(2, -0.7), 2);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	const Point &one = pointsBeside.front();
	const Point &two = pointsBeside.back();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, one.getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, two.getX(), 0.0001);
	CPPUNIT_ASSERT(one.getY() > 0.3 || one.getY() < -1.7);
	CPPUNIT_ASSERT(two.getY() > 0.3 || two.getY() < -1.7);
}

bool RouterTest::routeIsInsideField(const Route &route, const FieldPositionChecker &field)
{
	assert(route.isValid());
	list<Point> points = route.getAllPoints();

	for (list<Point>::const_iterator i = points.begin(); i != points.end(); ++i)
		if (!field.isPointInsideField(*i))
			return false;

	return true;
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_shortPointIsCorrect()
{
	RouterImpl router(0.5);
	Path currentPath(Point(0,0), Point(4,0), 0.5);
	Circle obstacle(Point(2,-0.5), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 0.707);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_longPointIsCorrect()
{
	RouterImpl router(0.5);
	Path currentPath(Point(0,0), Point(4,0), 0.5);
	Circle obstacle(Point(2,-0.5), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 0.707);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_bigObstacleCloseOnLeftSide_onePointIsLeftAndOneRight()
{
	RouterImpl router(0.5);
	Point start(3, -1.3606);
	Point end(5, 0);
	Circle obstacle(Point(3, 0), 2);
	Path path(start, end, 0.5);

	vector<Point> points = router.getPointsBesideObstacle(path, obstacle);

	Circle robotShortObstacle(points.front(), 0.707);
	CPPUNIT_ASSERT(!robotShortObstacle.overlapsWith(obstacle));
	Circle robotLongObstacle(points.back(), 0.707);
	CPPUNIT_ASSERT(!robotLongObstacle.overlapsWith(obstacle));

	Line line(start, end);
	CPPUNIT_ASSERT(path.intersectsWith(obstacle));
	CPPUNIT_ASSERT_EQUAL((size_t)2, points.size());
	CPPUNIT_ASSERT(line.isOnePointLeftAndOneRightOfLine(points[0], points[1]));
}

void RouterTest::getPointsBesideObstacle_bigObstacle_newStartBesideObstacleDoesntIntersectWithObstacleInWorstCaseOrientationFromStart()
{
	RouterImpl router(0.5);
	Point start(0, 0);
	Point end(5, 0);
	Circle obstacle(Point(3, 0), 2);
	Path path(start, end, 0.5);

	vector<Point> points = router.getPointsBesideObstacle(path, obstacle);

	CPPUNIT_ASSERT(points.size() == 2);
	const Point &pointOne = points.front();
	const Point &pointTwo = points.back();
	Point pointOneNext = pointOne + Point(5, 0);
	Point pointTwoNext = pointTwo + Point(5, 0);
	Path pathOne(pointOne, pointOneNext, 0.5);
	Path pathTwo(pointTwo, pointTwoNext, 0.5);
	PathIntersectPoints intersectionPointsOne = pathOne.getIntersectPoints(obstacle);
	PathIntersectPoints intersectionPointsTwo = pathTwo.getIntersectPoints(obstacle);
	CPPUNIT_ASSERT(intersectionPointsOne.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeFromStart);
	CPPUNIT_ASSERT(intersectionPointsTwo.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeFromStart);
}

void RouterTest::detectLoopInConsideredObstacles_noObstacles_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_oneObstacle_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacle_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacleAtEnd_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(-2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 5), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_thriceTheSameObstacle_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacleInTheMiddle_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(-3, 3), 2), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacleAtBegin_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_loopOverOne_true()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_loopOverTwo_true()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_sameAsSecond_true()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(1, 1), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(1, 1), 0.25), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_somewhereInBetweenALoop_false()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(1, 1), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(1, 1), 0.25), true));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_triedOnceLeftAndRightBesideSameObstacleDirectFollowed_true()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), false));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_triedOnceLeftAndRightBesideSameObstacle_true()
{
	RouterImpl router(0.5);
	list<RoutingObstacle> obstacles;
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 4), 0.5), true));
	obstacles.push_back(RoutingObstacle(Circle(Point(2, 3), 1), false));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::getPointsBesideObstacle_obstacleAtStart_resultSizeIs0()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(-1.5,0), 2);

	CPPUNIT_ASSERT_EQUAL((size_t)2, currentPath.getIntersectPoints(obstacle).getIntersectPoints().size());
	CPPUNIT_ASSERT_EQUAL(PathIntersectPoints::IntersectTypeFromStart, currentPath.getIntersectPoints(obstacle).getIntersectTypeFrom());
	CPPUNIT_ASSERT_EQUAL((size_t)0, router.getPointsBesideObstacle(currentPath, obstacle).size());
}

void RouterTest::getPointsBesideObstacle_obstacleAtEnd_resultSizeIs0()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(5.5,0), 2);

	CPPUNIT_ASSERT_EQUAL((size_t)2, currentPath.getIntersectPoints(obstacle).getIntersectPoints().size());
	CPPUNIT_ASSERT_EQUAL(PathIntersectPoints::IntersectTypeFromEnd, currentPath.getIntersectPoints(obstacle).getIntersectTypeFrom());
	CPPUNIT_ASSERT_EQUAL((size_t)0, router.getPointsBesideObstacle(currentPath, obstacle).size());
}
