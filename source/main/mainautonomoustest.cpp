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
	StorageImpl storage(15, TeamColorRed, logger, watch);
	FieldPositionCheckerGoalkeeper fieldPositionCheckerGoalKeeper;
	FieldPositionCheckerFieldPlayer fieldPositionCheckerFieldPlayer;
	TeamImpl team(storage, watch, logger, fieldPositionCheckerGoalKeeper, fieldPositionCheckerFieldPlayer);
	Robot &robot = team.getSecondFieldPlayer();
	cout << "objects created" << endl;

	do
	{
		Point targetOne(0.5, 0);
		Point targetTwo(-0.5, 0);

		robot.goToDirect(Pose(targetOne, Angle(0)));
		for (unsigned int i = 0; i < 500; ++i)
		{
			robot.measure();
			robot.update();
			usleep(10000);
		}

		cout << "error: " << targetOne.distanceTo(robot.getCurrentPose().getPosition()) << endl;
		if (robot.targetReached())
			cout << "target reached" << endl;
		else
			cout << "target not reached" << endl;

		robot.goToDirect(Pose(targetTwo, Angle(0)));
		for (unsigned int i = 0; i < 500; ++i)
		{
			robot.measure();
			robot.update();
			usleep(10000);
		}

		cout << "error: " << targetTwo.distanceTo(robot.getCurrentPose().getPosition()) << endl;
		if (robot.targetReached())
			cout << "target reached" << endl;
		else
			cout << "target not reached" << endl;
	} while (true);

	cout << "reached target" << endl;
	return 0;
}
