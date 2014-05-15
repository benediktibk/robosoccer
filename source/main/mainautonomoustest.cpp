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
	cout << "initialization finished" << endl;

	robotOne.goTo(Pose(Point(-1, 0), Angle(0)));
	robotTwo.goTo(Pose(Point(0, 0), Angle(0)));
	robotThree.goTo(Pose(Point(1, 0), Angle(0)));
	robotOne.update();
	robotTwo.update();
	robotThree.update();

//	while(true)
//	{
//		robotOne.goToDirect(Pose(Point(1, 0.5), Angle()));
//		robotTwo.goToDirect(Pose(Point(1, 0), Angle()));
//		robotThree.goToDirect(Pose(Point(1, -0.5), Angle()));
//		for (unsigned int i = 0; i < 1200; ++i)
//		{
//			robotOne.update();
//			robotTwo.update();
//			robotThree.update();
//			usleep(5000);
//		}

//		robotOne.goToDirect(Pose(Point(-1, 0.5), Angle()));
//		robotTwo.goToDirect(Pose(Point(-1, 0), Angle()));
//		robotThree.goToDirect(Pose(Point(-1, -0.5), Angle()));
//		for (unsigned int i = 0; i < 1200; ++i)
//		{
//			robotOne.update();
//			robotTwo.update();
//			robotThree.update();
//			usleep(5000);
//		}
//	}

//	IntelligentBallImpl ball(storage.getBall());
//	while(true)
//	{
//		robotOne.goToDirect(Pose(ball.getPosition(), Angle(robotOne.getCurrentPose().getPosition(), ball.getPosition())));
//		robotOne.update();
//		usleep(5000);
//	}

//	IntelligentBallImpl ball(storage.getBall());
//	TargetPositionFetcher targetPositionFetcher;
//	targetPositionFetcher.setFieldSide(FieldSideLeft);
//	fstream ballPositions;
//	fstream goaliePositions;
//	ballPositions.open("ball.dat", ios_base::out | ios_base::trunc);
//	goaliePositions.open("goalie.dat", ios_base::out | ios_base::trunc);
//	while(true)
//	{
//		Point ballPosition = ball.getPosition();
//		Pose targetPose = targetPositionFetcher.getPenaltyPositionGoalie(ball);
//		ballPositions << ballPosition.getX() << " " << ballPosition.getY() << endl;
//		goaliePositions << targetPose.getPosition().getX() << " " << targetPose.getPosition().getY() << endl;
//		robotOne.goToDirect(targetPose);
//		robotOne.update();
//		usleep(30000);
//		ballPositions.flush();
//		goaliePositions.flush();
//	}

	return 0;
}
