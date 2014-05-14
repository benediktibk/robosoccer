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
#include <math.h>

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
	Robot &robotOne = team.getFirstFieldPlayer();
	Robot &robotTwo = team.getSecondFieldPlayer();
	Robot &robotThree = team.getGoalie();

	while(true)
	{
		robotOne.goToDirect(Pose(Point(1, 0.5), Angle()));
		robotTwo.goToDirect(Pose(Point(1, 0), Angle()));
		robotThree.goToDirect(Pose(Point(1, -0.5), Angle()));
		for (unsigned int i = 0; i < 1200; ++i)
		{
			robotOne.update();
			robotTwo.update();
			robotThree.update();
			usleep(5000);
		}

		robotOne.goToDirect(Pose(Point(-1, 0.5), Angle()));
		robotTwo.goToDirect(Pose(Point(-1, 0), Angle()));
		robotThree.goToDirect(Pose(Point(-1, -0.5), Angle()));
		for (unsigned int i = 0; i < 1200; ++i)
		{
			robotOne.update();
			robotTwo.update();
			robotThree.update();
			usleep(5000);
		}
	}

	return 0;
}
