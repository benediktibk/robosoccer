#include "layer/abstraction/storageimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/main/fieldpositioncheckergoalkeeper.h"
#include "layer/main/fieldpositioncheckerfieldplayer.h"
#include "layer/autonomous/robot.h"
#include "common/logging/loggerimpl.h"
#include "common/time/watchimpl.h"
#include "common/geometry/pose.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Layer::Main;
using namespace std;

int main(int, char**)
{
	cout << "creating objects" << endl;
	LoggerImpl logger;
	WatchImpl watch;
	StorageImpl storage(14, TeamColorBlue, logger, watch);
	FieldPositionCheckerGoalkeeper fieldPositionCheckerGoalKeeper;
	FieldPositionCheckerFieldPlayer fieldPositionCheckerFieldPlayer;
	TeamImpl team(storage, watch, logger, fieldPositionCheckerGoalKeeper, fieldPositionCheckerFieldPlayer);
	IntelligentBallImpl ball(storage.getBall());
	Robot &robot = team.getFirstFieldPlayer();
	TargetPositionFetcher targetPositionFetcher;
	cout << "objects created" << endl;

	cout << "moving to the ball" << endl;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	robot.goTo(targetPositionFetcher.getPenaltyPositionKicker(ball));
	robot.update();
	sleep(2);

	cout << "kicking the ball" << endl;
	cout << "current robot position: " << robot.getCurrentPose().getPosition() << endl;
	cout << "current ball position: " << ball.getPosition() << endl;
	robot.kick(100, ball);

	for (unsigned int i = 0; i < 1000; ++i)
	{
		robot.update();
		usleep(10000);
	}

	return 0;
}
