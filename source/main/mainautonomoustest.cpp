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
	fieldPositionCheckerGoalKeeper.setFieldSide(FieldSideRight);

	obstacleFetcher.addSource(robotOne);
	obstacleFetcher.addSource(robotTwo);
	obstacleFetcher.addSource(robotThree);
	obstacleFetcher.addSource(enemyTeam);
	obstacleFetcher.addSource(ball);
	obstacleFetcher.defineBall(ball);

//	while(true)
//	{
//		vector<Pose> target;
//		target.push_back(Pose(Point(0.2, 0), Angle::getQuarterRotation()));
//		robotThree.goTo(target, DriveModeDefault);
//		while (!robotThree.reachedTarget())
//		{
//			robotThree.update();
//			usleep(10000);
//		}
//		cout << "reached target" << endl;

//		target.clear();
//		target.push_back(Pose(Point(1.3, 0), Angle::getQuarterRotation()));
//		robotThree.goTo(target, DriveModeIgnoreGoalObstacles);
//		while (!robotThree.reachedTarget())
//		{
//			robotThree.update();
//			usleep(10000);
//		}
//		cout << "reached target" << endl;
//	}

//	while(true)
//	{
//		Pose targetOne(Point(0.1, 0), Angle());
//		robotOne.goToDirect(targetOne);
//		while (!robotOne.reachedTarget())
//		{
//			robotOne.update();
//			usleep(10000);
//		}

//		cout << targetOne.getPosition().distanceTo(robotOne.getCurrentPose().getPosition()) << endl;

//		Pose targetTwo(Point(-0.1, 0), Angle());
//		robotOne.goToDirect(targetTwo);
//		while (!robotOne.reachedTarget())
//		{
//			robotOne.update();
//			usleep(10000);
//		}

//		cout << targetTwo.getPosition().distanceTo(robotOne.getCurrentPose().getPosition()) << endl;
//	}

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

	Robot &robot = robotTwo;
	robot.goToDirect(Pose(Point(1.4, 0), Angle(0)));
	cout << "driving to start position" << endl;
	while(!robot.reachedTarget())
	{
		robot.updateActuators();
		usleep(10000);
	}

	cout << "reached start position" << endl;
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	while(true)
	{
		ball.update();
		Pose targetPose = targetPositionFetcher.getTargetForGoalkeeper(ball);
		robot.goToDirect(targetPose);
		robot.updateActuators();
		usleep(10000);
	}

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
