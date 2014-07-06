#include "layer/abstraction/storageimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/abstraction/fieldpositioncheckerfieldplayer.h"
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
using namespace std;

int main(int, char**)
{
	cout << "creating objects" << endl;
	LoggerImpl logger;
	WatchImpl watch;
	StorageImpl storage(14, TeamColorBlue, logger, watch);
	FieldPositionCheckerGoalkeeper fieldPositionCheckerGoalKeeper;
	FieldPositionCheckerFieldPlayer fieldPositionCheckerFieldPlayer;
	ObstacleFetcherImpl obstacleFetcher;
	TeamImpl team(storage, watch, logger, fieldPositionCheckerGoalKeeper, fieldPositionCheckerFieldPlayer, obstacleFetcher);
	EnemyTeamImpl enemyTeam(storage);
	IntelligentBallImpl ball(storage.getBall());
	Robot &robotOne = team.getFirstFieldPlayer();
	Robot &robotTwo = team.getSecondFieldPlayer();
	Robot &robotThree = team.getGoalie();
	cout << "initialization finished" << endl;
	fieldPositionCheckerGoalKeeper.setFieldSide(FieldSideRight);

	obstacleFetcher.addSource(robotOne);
	obstacleFetcher.addSource(robotTwo);
	obstacleFetcher.addSource(robotThree);
	obstacleFetcher.addSource(enemyTeam);
	obstacleFetcher.addSource(ball);
	obstacleFetcher.defineBall(ball);

	Robot &robot = robotTwo;
	while(true)
	{
		vector<Pose> targets;
		targets.push_back(Pose(Point(-0.5, 0), Angle(0)));
		robot.goTo(targets, DriveModeDefault);
		while (!robot.reachedTarget())
		{
			ball.update();
			enemyTeam.updateSensors();
			team.updateSensors();
			team.updateActuators();
			usleep(10000);
		}

		targets.clear();
		targets.push_back(Pose(Point(0.5, 0), Angle(0)));
		robot.goTo(targets, DriveModeDefault);
		while (!robot.reachedTarget())
		{
			ball.update();
			enemyTeam.updateSensors();
			team.updateSensors();
			team.updateActuators();
			usleep(10000);
		}
	}

	return 0;
}
