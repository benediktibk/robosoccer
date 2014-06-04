#include "layer/abstraction/storageimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/intelligentballimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/obstaclefetcherimpl.h"
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
	StorageImpl storage(14, TeamColorRed, logger, watch);
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

	obstacleFetcher.addSource(robotOne);
	obstacleFetcher.addSource(robotTwo);
	obstacleFetcher.addSource(robotThree);
	obstacleFetcher.addSource(enemyTeam);
	obstacleFetcher.addSource(ball);
	obstacleFetcher.defineBall(ball);

	while(true)
	{
		robotOne.goTo(Pose(Point(1, 0), Angle::getQuarterRotation()), false, false, false);
		while (!robotOne.targetReached())
		{
			robotOne.update();
			usleep(10000);
		}

		robotOne.goTo(Pose(Point(0, 0), Angle::getQuarterRotation()), false, false, false);
		while (!robotOne.targetReached())
		{
			robotOne.update();
			usleep(10000);
		}
	}

//	robotTwo.goTo(Pose(Point(0, 0.5), Angle::getQuarterRotation()), false, false);
//	while (!robotTwo.targetReached())
//	{
//		robotTwo.update();
//		usleep(10000);
//	}

//	while(true)
//	{
//		robotOne.goToDirect(Pose(ball.getPosition(), Angle(robotOne.getCurrentPose().getPosition(), ball.getPosition())));
//		robotOne.update();
//		usleep(5000);
//	}

//	robotThree.goTo(Pose(Point(1.40, 0), Angle::getQuarterRotation()), false, false, true);
//	while (!robotThree.targetReached())
//	{
//		robotThree.update();
//		usleep(10000);
//	}
//	cout << "done";

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

//	TargetPositionFetcher targetPositionFetcher;
//	targetPositionFetcher.setFieldSide(FieldSideLeft);
//	Pose targetPose = targetPositionFetcher.getPenaltyPositionKicker(ball);
//	robotOne.goToDirect(targetPose);
//	robotOne.update();
//	while(!robotOne.targetReached())
//	{
//		robotOne.update();
//		usleep(10000);
//	}

//	robotOne.kick(ball);
//	robotOne.update();
//	while(!robotOne.targetReached())
//	{
//		robotOne.update();
//		usleep(10000);
//	}

	return 0;
}
