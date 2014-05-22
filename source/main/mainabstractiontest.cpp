#include "layer/abstraction/ballimpl.h"
#include "layer/abstraction/readablerobotimpl.h"
#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/refereebase.h"
#include "common/geometry/point.h"
#include "common/geometry/pose.h"
#include "common/logging/loggerimpl.h"
#include "common/time/watchimpl.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace std;

int main(int, char**)
{
	cout << "creating objects from database" << endl;
	LoggerImpl logger;
	WatchImpl watch;
	StorageImpl storage(14, TeamColorRed, logger, watch);
	Ball const& ball = storage.getBall();
	ReadableRobot const& enemyRobot = storage.getEnemyRobot(0);
	ControllableRobot &ownRobot = storage.getOwnRobot(2);
	RefereeBase &referee = storage.getReferee();

	cout << "current ball position is " << ball.getPosition() << endl;
	cout << "current ball orientation is " << ball.getRotation() << endl;
	cout << "current pose of enemy robot is " << enemyRobot.getPose() << endl;
	cout << "current pose of own robot is " << ownRobot.getPose() << endl;
	referee.logInformation();

//	ownRobot.kick(100);
//	for (unsigned int i = 0; i < 1000; ++i)
//	{
//		ownRobot.update();
//		usleep(10000);
//	}

//	while(true)
//	{
//		Point targetOne(0.5, 0);
//		Point targetTwo(-0.5, 0);

//		ownRobot.gotoPositionImprecise(targetOne);
//		for (unsigned int i = 0; i < 1000; ++i)
//		{
//			ownRobot.measure();
//			ownRobot.update();
//			usleep(10000);
//		}

//		cout << "error: " << targetOne.distanceTo(ownRobot.getPose().getPosition()) << endl;
//		if (ownRobot.isMoving())
//			cout << "not moving anymore" << endl;
//		else
//			cout << "still moving " << endl;

//		ownRobot.gotoPositionImprecise(targetTwo);
//		for (unsigned int i = 0; i < 1000; ++i)
//		{
//			ownRobot.measure();
//			ownRobot.update();
//			usleep(10000);
//		}

//		cout << "error: " << targetTwo.distanceTo(ownRobot.getPose().getPosition()) << endl;
//		if (ownRobot.isMoving())
//			cout << "not moving anymore" << endl;
//		else
//			cout << "still moving " << endl;
//	}

//	ownRobot.gotoPositionImprecise(Point(-1, 0));
//	for (unsigned int i = 0; i < 400; ++i)
//	{
//		ownRobot.update();
//		usleep(10000);
//	}

	while(true)
	{
		for (unsigned int i = 0; i < 200; ++i)
		{
			ownRobot.turn(Angle(0));
			ownRobot.update();
			usleep(10000);
		}
		cout << ownRobot.getPose().getOrientation() << endl;

		for (unsigned int i = 0; i < 200; ++i)
		{
			ownRobot.turn(Angle(0.5));
			ownRobot.update();
			usleep(10000);
		}
		cout << ownRobot.getPose().getOrientation() - Angle(0.5) << endl;
	}

	return 0;
}
