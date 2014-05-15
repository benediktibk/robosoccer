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
	StorageImpl storage(15, TeamColorBlue, logger, watch);
	FieldPositionCheckerGoalkeeper fieldPositionCheckerGoalKeeper;
	FieldPositionCheckerFieldPlayer fieldPositionCheckerFieldPlayer;
	TeamImpl team(storage, watch, logger, fieldPositionCheckerGoalKeeper, fieldPositionCheckerFieldPlayer);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallImpl ball(storage.getBall());

	targetPositionFetcher.setFieldSide(FieldSideLeft);
	Robot &robot1 = team.getFirstFieldPlayer();
	Robot &robot2 = team.getSecondFieldPlayer();
	Robot &robotGoalie = team.getGoalie();

	cout << "objects created" << endl;

	robot1.goToDirect(targetPositionFetcher.getStartPositionPlayerOneOffensive());
	robot2.goToDirect(targetPositionFetcher.getStartPositionPlayerTwoOffensive());
	robotGoalie.goToDirect(targetPositionFetcher.getStartPositionGoalkeeper());

//	robot1.goToDirect(targetPositionFetcher.getStartPositionPlayerOneDefensive());
//	robot2.goToDirect(targetPositionFetcher.getStartPositionPlayerTwoDefensive());
//	robotGoalie.goToDirect(targetPositionFetcher.getStartPositionGoalkeeper());

	while(true)
	{
		robot1.update();
		robot2.update();
		robotGoalie.update();

		usleep(10000);
	}

	return 0;
}
